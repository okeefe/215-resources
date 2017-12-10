/**************************************************************************/
/***************************************************************************

   HELLOSERVER.C - a 'Hello World' TCP/IP based server daemon

   Implements a skeleton of a single process iterative server
   daemon.

   Wherever possible the code adheres to POSIX.

   David Gillies <daggillies@yahoo.com> Sep 2003

   Placed in the public domain. Unrestricted use or modification
   of this code is permitted without attribution to the author.

***************************************************************************/
/**************************************************************************/

#ifdef __GNUC__
#define _GNU_SOURCE /* for strsignal() */
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <syslog.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*************************************************************************/

/* global variables and constants */

volatile sig_atomic_t	gGracefulShutdown=0;
volatile sig_atomic_t	gCaughtHupSignal=0;

int							gLockFileDesc=-1;
int							gMasterSocket=-1;

/* the 'well-known' port on which our server will be listening */

const int					gHelloServerPort=30153;

/* the path to our lock file */

const char *const			gLockFilePath="/var/run/helloserver.pid";

/*************************************************************************/

/* prototypes */

int BecomeDaemonProcess(const char *const lockFileName,
								const char *const logPrefix,
								const int logLevel,
								int *const lockFileDesc,
								int *const thisPID);
int ConfigureSignalHandlers(void);
int BindPassiveSocket(const unsigned long interfaceAddress,
							 const int portNum,
							 int *const boundSocket);
int AcceptConnections(const int master);
int HandleConnection(const int slave);
int WriteToSocket(const int sock,const char *const buffer,
						const size_t buflen);
int ReadLine(const int sock,char *const buffer,const size_t buflen,
				 size_t *const bytesRead);
void FatalSigHandler(int sig);
void TermHandler(int sig);
void HupHandler(int sig);
void Usr1Handler(int sig);
void TidyUp(void);

/*************************************************************************/

/* an idea from 'Advanced Programming in the Unix Environment'
	Stevens 1993 - see BecomeDaemonProcess() */

#define OPEN_MAX_GUESS 256

/*************************************************************************/

int main(void /*int argc,char *argv[]*/)
{
	int						result;
	pid_t						daemonPID;
	
	/*************************************************************/
	/* perhaps at this stage you would read a configuration file */
	/*************************************************************/

	/* the first task is to put ourself into the background (i.e
		become a daemon. */

	if((result=BecomeDaemonProcess(gLockFilePath,"helloserver",
											 LOG_DEBUG,&gLockFileDesc,&daemonPID))<0)
		{
		perror("Failed to become daemon process");
		exit(result);
		}

	/* set up signal processing */

	if((result=ConfigureSignalHandlers())<0)
		{
		syslog(LOG_LOCAL0|LOG_INFO,"ConfigureSignalHandlers failed, errno=%d",errno);
		unlink("/var/log/helloserver.pid");
		exit(result);
		}

	/* now we must create a socket and bind it to a port */

	if((result=BindPassiveSocket(INADDR_ANY,gHelloServerPort,&gMasterSocket))<0)
		{
		syslog(LOG_LOCAL0|LOG_INFO,"BindPassiveSocket failed, errno=%d",errno);
		unlink("/var/log/helloserver.pid");
		exit(result);
		}

	/* now enter an infinite loop handling connections */

	do
		{
		if(AcceptConnections(gMasterSocket)<0)
			{
			syslog(LOG_LOCAL0|LOG_INFO,"AcceptConnections failed, errno=%d",errno);
			unlink("/var/log/helloserver.pid");
			exit(result);
			}
		
		/* the next conditional will be true if we caught signal SIGUSR1 */

		if((gGracefulShutdown==1)&&(gCaughtHupSignal==0))
			break;

		/* if we caught SIGHUP, then start handling connections again */

		gGracefulShutdown=gCaughtHupSignal=0;
		}while(1);

	TidyUp(); /* close the socket and kill the lock file */

	return 0;
}

/**************************************************************************/
/***************************************************************************

   BecomeDaemonProcess

	Fork the process into the background, make a lock file, and open the
   system log.

	Inputs:

   lockFileName I					  the path to the lock file

   logPrefix	 I					  the string that will appear at the
										  start of all log messages

   logLevel		 I					  the logging level for this process

   lockFileDesc O					  the file descriptor of the lock file

   thisPID		 O					  the PID of this process after fork()
										  has placed it in the background
	Returns:

	status code indicating success - 0 = success
	
***************************************************************************/
/**************************************************************************/

int BecomeDaemonProcess(const char *const lockFileName,
								const char *const logPrefix,
								const int logLevel,
								int *const lockFileDesc,
								pid_t *const thisPID)
{
	int						curPID,stdioFD,lockResult,killResult,lockFD,i,
								numFiles;
	char						pidBuf[17],*lfs,pidStr[7];
	FILE						*lfp;
	unsigned long			lockPID;
	struct flock			exclusiveLock;

	/* set our current working directory to root to avoid tying up
		any directories. In a real server, we might later change to
		another directory and call chroot() for security purposes
		(especially if we are writing something that serves files */

	chdir("/");
	
	/* try to grab the lock file */

	lockFD=open(lockFileName,O_RDWR|O_CREAT|O_EXCL,0644);
	
	if(lockFD==-1)
		{
		/* Perhaps the lock file already exists. Try to open it */

		lfp=fopen(lockFileName,"r");

		if(lfp==0) /* Game over. Bail out */
			{
			perror("Can't get lockfile");
			return -1;
			}

		/* We opened the lockfile. Our lockfiles store the daemon PID in them.
			Find out what that PID is */

		lfs=fgets(pidBuf,16,lfp);

		if(lfs!=0)
			{
			if(pidBuf[strlen(pidBuf)-1]=='\n') /* strip linefeed */
				pidBuf[strlen(pidBuf)-1]=0;
			
			lockPID=strtoul(pidBuf,(char**)0,10);
			
			/* see if that process is running. Signal 0 in kill(2) doesn't
				send a signal, but still performs error checking */
			
			killResult=kill(lockPID,0);
			
			if(killResult==0)
				{
				printf("\n\nERROR\n\nA lock file %s has been detected. It appears it is owned\nby the (active) process with PID %ld.\n\n",lockFileName,lockPID);
				}
			else
				{
				if(errno==ESRCH) /* non-existent process */
					{
					printf("\n\nERROR\n\nA lock file %s has been detected. It appears it is owned\nby the process with PID %ld, which is now defunct. Delete the lock file\nand try again.\n\n",lockFileName,lockPID);
					}
				else
					{
					perror("Could not acquire exclusive lock on lock file");
					}
				}
			}
		else
			perror("Could not read lock file");

		fclose(lfp);
		
		return -1;
		}

	/* we have got this far so we have acquired access to the lock file.
		Set a lock on it */

	exclusiveLock.l_type=F_WRLCK; /* exclusive write lock */
	exclusiveLock.l_whence=SEEK_SET; /* use start and len */
	exclusiveLock.l_len=exclusiveLock.l_start=0; /* whole file */
	exclusiveLock.l_pid=0; /* don't care about this */
	lockResult=fcntl(lockFD,F_SETLK,&exclusiveLock);
	
	if(lockResult<0) /* can't get a lock */
		{
		close(lockFD);
		perror("Can't get lockfile");
		return -1;
		}

	/* now we move ourselves into the background and become a daemon.
	 Remember that fork() inherits open file descriptors among others so
	 our lock file is still valid */

	curPID=fork();

	switch(curPID)
		{
		case 0: /* we are the child process */
		  break;

		case -1: /* error - bail out (fork failing is very bad) */
		  fprintf(stderr,"Error: initial fork failed: %s\n",
					 strerror(errno));
		  return -1;
		  break;

		default: /* we are the parent, so exit */
		  exit(0);
		  break;
		}

	/* make the process a session and process group leader. This simplifies
		job control if we are spawning child servers, and starts work on
		detaching us from a controlling TTY	*/

	if(setsid()<0)
		return -1;
	
	/* ignore SIGHUP as this signal is sent when session leader terminates */

	signal(SIGHUP,SIG_IGN);

	/* fork again to let session group leader exit. Now we can't
		have a controlling TTY. */

	curPID=fork();

	switch(curPID) /* return codes as before */
		{
		case 0:
		  break;

		case -1:
		  return -1;
		  break;

		default:
		  exit(0);
		  break;
		}

	/* log PID to lock file */

	/* truncate just in case file already existed */
	
	if(ftruncate(lockFD,0)<0)
		return -1;

	/* store our PID. Then we can kill the daemon with
		kill `cat <lockfile>` where <lockfile> is the path to our
		lockfile */
	
	sprintf(pidStr,"%d\n",(int)getpid());
	
	write(lockFD,pidStr,strlen(pidStr));

	*lockFileDesc=lockFD; /* return lock file descriptor to caller */
	
	/* close open file descriptors */

	numFiles=sysconf(_SC_OPEN_MAX); /* how many file descriptors? */
	
	if(numFiles<0) /* sysconf has returned an indeterminate value */
		numFiles=OPEN_MAX_GUESS; /* from Stevens '93 */
		
	for(i=numFiles-1;i>=0;--i) /* close all open files except lock */
		{
		if(i!=lockFD) /* don't close the lock file! */
			close(i);
		}
	
	/* stdin/out/err to /dev/null */

	umask(0); /* set this to whatever is appropriate for you */

	stdioFD=open("/dev/null",O_RDWR); /* fd 0 = stdin */
	dup(stdioFD); /* fd 1 = stdout */
	dup(stdioFD); /* fd 2 = stderr */

	/* open the system log - here we are using the LOCAL0 facility */

	openlog(logPrefix,LOG_PID|LOG_CONS|LOG_NDELAY|LOG_NOWAIT,LOG_LOCAL0);

	(void)setlogmask(LOG_UPTO(logLevel)); /* set logging level */

	/* put server into its own process group. If this process now spawns
		child processes, a signal sent to the parent will be propagated
		to the children */

	setpgrp();

	return 0;
}

/**************************************************************************/
/***************************************************************************

   ConfigureSignalHandlers

	Set up the behaviour of the various signal handlers for this process.
   Signals are divided into three groups: those we can ignore; those that
   cause a fatal error but in which we are not particularly interested and
   those that are used to control the server daemon. We don't bother with
   the new real-time signals under Linux since these are blocked by default
   anyway.

	Returns: none

***************************************************************************/
/**************************************************************************/

int ConfigureSignalHandlers(void)
{
	struct sigaction		sighupSA,sigusr1SA,sigtermSA;

	/* ignore several signals because they do not concern us. In a
		production server, SIGPIPE would have to be handled as this
		is raised when attempting to write to a socket that has
		been closed or has gone away (for example if the client has
		crashed). SIGURG is used to handle out-of-band data. SIGIO
		is used to handle asynchronous I/O. SIGCHLD is very important
		if the server has forked any child processes. */

	signal(SIGUSR2,SIG_IGN);	
	signal(SIGPIPE,SIG_IGN);
	signal(SIGALRM,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	signal(SIGTTOU,SIG_IGN);
	signal(SIGURG,SIG_IGN);
	signal(SIGXCPU,SIG_IGN);
	signal(SIGXFSZ,SIG_IGN);
	signal(SIGVTALRM,SIG_IGN);
	signal(SIGPROF,SIG_IGN);
	signal(SIGIO,SIG_IGN);
	signal(SIGCHLD,SIG_IGN);

	/* these signals mainly indicate fault conditions and should be logged.
		Note we catch SIGCONT, which is used for a type of job control that
		is usually inapplicable to a daemon process. We don't do anyting to
		SIGSTOP since this signal can't be caught or ignored. SIGEMT is not
		supported under Linux as of kernel v2.4 */

	signal(SIGQUIT,FatalSigHandler);
	signal(SIGILL,FatalSigHandler);
	signal(SIGTRAP,FatalSigHandler);
	signal(SIGABRT,FatalSigHandler);
	signal(SIGIOT,FatalSigHandler);
	signal(SIGBUS,FatalSigHandler);
#ifdef SIGEMT /* this is not defined under Linux */
	signal(SIGEMT,FatalSigHandler);
#endif
	signal(SIGFPE,FatalSigHandler);
	signal(SIGSEGV,FatalSigHandler);
	signal(SIGSTKFLT,FatalSigHandler);
	signal(SIGCONT,FatalSigHandler);
	signal(SIGPWR,FatalSigHandler);
	signal(SIGSYS,FatalSigHandler);
	
	/* these handlers are important for control of the daemon process */

	/* TERM  - shut down immediately */
	
	sigtermSA.sa_handler=TermHandler;
	sigemptyset(&sigtermSA.sa_mask);
	sigtermSA.sa_flags=0;
	sigaction(SIGTERM,&sigtermSA,NULL);
		
	/* USR1 - finish serving the current connection and then close down
		(graceful shutdown) */
	
	sigusr1SA.sa_handler=Usr1Handler;
	sigemptyset(&sigusr1SA.sa_mask);
	sigusr1SA.sa_flags=0;
	sigaction(SIGUSR1,&sigusr1SA,NULL);
	
	/* HUP - finish serving the current connection and then restart
		connection handling. This could be used to force a re-read of
		a configuration file for example */
	
	sighupSA.sa_handler=HupHandler;
	sigemptyset(&sighupSA.sa_mask);
	sighupSA.sa_flags=0;
	sigaction(SIGHUP,&sighupSA,NULL);
	
	return 0;
}

/**************************************************************************/
/***************************************************************************

   BindPassiveSocket

	Create a socket, bind it to a port and then place it in passive
	(listen) mode to handle client connections.

	Inputs:

	interface	 I					  the IP address that should be bound
										  to the socket. This is important for
										  multihomed hosts, which may want to 
										  restrict themselves to listening on a
										  given interface. If this is not the case,
										  use the special constant INADDR_ANY to
										  listen on all interfaces.

	Returns:

	status code indicating success - 0 = success
	
***************************************************************************/
/**************************************************************************/

int BindPassiveSocket(const unsigned long interface,
							 const int portNum,
							 int *const boundSocket)
{
	struct sockaddr_in			  sin;
	struct protoent				  *proto;
	int								  newsock,optval;
	size_t							  optlen;
	
	/* get the number of the TCP protocol */
	if((proto=getprotobyname("tcp"))==NULL)
		return -1;

	/* clear the socket address structure */
	
	memset(&sin.sin_zero,0,8);

	/* set up the fields. Note htonX macros are important for
		portability */

	sin.sin_port=htons(portNum);
	sin.sin_family=AF_INET; /* Usage: AF_XXX here, PF_XXX in socket() */
	sin.sin_addr.s_addr=htonl(interface);

	if((newsock=socket(PF_INET,SOCK_STREAM,proto->p_proto))<0)
		return -1;
	
	/* The SO_REUSEADDR socket option allows the kernel to re-bind
		local addresses without delay (for our purposes, it allows re-binding
		while the previous socket is in TIME_WAIT status, which lasts for
		two times the Maximum Segment Lifetime - anything from
		30 seconds to two minutes). It should be used with care as in
		general you don't want two processes sharing the same port. There are
		also dangers if a client tries to re-connect to the same port a
		previous server used within the 2*MSL window that TIME_WAIT provides.
		It's handy for us so the server can be restarted without having to
		wait for termination of the TIME_WAIT period. */

	optval=1;
	optlen=sizeof(int);
	setsockopt(newsock,SOL_SOCKET,SO_REUSEADDR,&optval,optlen);
	
	/* bind to the requested port */
	
	if(bind(newsock,(struct sockaddr*)&sin,sizeof(struct sockaddr_in))<0)
		return -1;
		  
	/* put the socket into passive mode so it is lisetning for connections */
		  
	if(listen(newsock,SOMAXCONN)<0)
		return -1;
	
	*boundSocket=newsock;
	
	return 0;
}

/* Note on restartable system calls:

several of the following functions check the return value from 'slow'
system calls (i.e. calls that can block indefinitely in the kernel)
and continue operation if the return value is EINTR. This error is
given if a system call is interrupted by a signal. However, many systems
can automatically restart system calls. Automatic restart is enabled by
setting the SA_RESTART flag in the sa_flags field of the struct sigaction.
We do not do this as we want the loop on accept() in AcceptConnections() to
look at the gGracefulShutdown flag which is set on recept of SIGHUP and
SIGUSR1 and is used to control the server.

You should still check for return code EINTR even if you have set SA_RESTART
to be on the safe side. Note that this simple behaviour WILL NOT WORK for
the connect() system call on many systems (although Linux appears to be an
exception). On such systems, you will need to call poll() or select() if
connect() is interrupted.

*/

/**************************************************************************/
/***************************************************************************

   AcceptConnections

	Repeatedly handle connections, blocking on accept() and then
	handing off the request to the HandleConnection function.
	
	Inputs:

	master		 I					  the master socket that has been
										  bound to a port and is listening
										  for connection attempts

	Returns:

	status code indicating success - 0 = success
	
***************************************************************************/
/**************************************************************************/

int AcceptConnections(const int master)
{
	int						proceed=1,slave,retval=0;
	struct sockaddr_in	client;
	socklen_t				clilen;

	while((proceed==1)&&(gGracefulShutdown==0))
		{
		/* block in accept() waiting for a request */

		clilen=sizeof(client);

		slave=accept(master,(struct sockaddr *)&client,&clilen);

		if(slave<0) /* accept() failed */
			{
			if(errno==EINTR)
				continue;

			syslog(LOG_LOCAL0|LOG_INFO,"accept() failed: %m\n");
			proceed=0;
			retval=-1;
			}
		else
			{
			retval=HandleConnection(slave); /* process connection */
			if(retval)
				proceed=0;
			}

		close(slave);
		}

	return retval;
}

/**************************************************************************/
/***************************************************************************

   HandleConnection

	Service connections from the client. In practice, this function
   would probably be used as a 'switchboard' to dispatch control to
   helper functions based on the exact content of the client request.
   Here, we simply read a CRLF-terminated line (the server is intended
   to be exercised for demo purposes via a telnet client) and echo it
   back to the client.
	
	Inputs:

	sock			 I					  the socket descriptor for this
										  particular connection event

	Returns:

	status code indicating success - 0 = success
   
***************************************************************************/
/**************************************************************************/

int HandleConnection(const int slave)
{
	char						readbuf[1025];
	size_t					bytesRead;
	const size_t			buflen=1024;
	int						retval;

	retval=ReadLine(slave,readbuf,buflen,&bytesRead);

	if(retval==0)
		WriteToSocket(slave,readbuf,bytesRead);
	
	return retval;
}

/**************************************************************************/
/***************************************************************************

   WriteToSocket

   Write a buffer full of data to a socket. Keep writing until
   all the data has been put into the socket.

   sock			 I					  the socket to read from

   buffer		 I					  the buffer into which the data
										  is to be deposited

   buflen		 I					  the length of the buffer in bytes

   Returns: status code indicating success - 0 = success
  
***************************************************************************/
/**************************************************************************/

int WriteToSocket(const int sock,const char *const buffer,
						const size_t buflen)
{
	size_t					bytesWritten=0;
	ssize_t					writeResult;
	int						retval=0,done=0;

	do
		{
		writeResult=send(sock,buffer+bytesWritten,buflen-bytesWritten,0);
		if(writeResult==-1)
			{
			if(errno==EINTR)
				writeResult=0;
			else
				{
				retval=1;
				done=1;
				}
			}
		else
			{
			bytesWritten+=writeResult;
			if(writeResult==0)
				done=1;
			}
		}while(done==0);

	return retval;
}

/**************************************************************************/
/***************************************************************************

   ReadLine

   Read a CRLF terminated line from a TCP socket. This is not
   the most efficient of functions, as it reads a byte at a
   time, but enhancements are beyond the scope of this example.

   sock			 I					  the socket to read from

   buffer		 O					  the buffer into which the data
										  is to be deposited

   buflen		 I					  the length of the buffer in bytes

   bytesRead	 O					  the amount of data read

   Returns: status code indicating success - 0 = success

***************************************************************************/
/**************************************************************************/

int ReadLine(const int sock,char *const buffer,const size_t buflen,
				 size_t *const bytesRead)
{
	int						done=0,retval=0;
	char						c,lastC=0;
	size_t					bytesSoFar=0;
	ssize_t					readResult;
	
	do
		{
		readResult=recv(sock,&c,1,0);
		
		switch(readResult)
			{
			case -1:
			  if(errno!=EINTR)
				  {
				  retval=-1;
				  done=1;
				  }
			  break;
			  
			case 0:
			  retval=0;
			  done=1;
			  break;
			  
			case 1:
			  buffer[bytesSoFar]=c;
			  bytesSoFar+=readResult;
			  if(bytesSoFar>=buflen)
				  {
				  done=1;
				  retval=-1;
				  }
			  
			  if((c=='\n')&&(lastC=='\r'))
				  done=1;
			  lastC=c;
			  break;
			}
		}while(!done);
	buffer[bytesSoFar]=0;
	*bytesRead=bytesSoFar;
	
	return retval;
}

/**************************************************************************/
/***************************************************************************

   FatalSigHandler

	General catch-all signal handler to mop up signals that we aren't
	especially interested in. It shouldn't be called (if it is it
	probably indicates an error). It simply dumps a report of the
	signal to the log and dies. Note the strsignal() function may not be
   available on all platform/compiler combinations.

	sig			 I					  the signal number

	Returns: none
																									 
***************************************************************************/
/**************************************************************************/

void FatalSigHandler(int sig)
{
#ifdef _GNU_SOURCE
	syslog(LOG_LOCAL0|LOG_INFO,"caught signal: %s - exiting",strsignal(sig));
#else
	syslog(LOG_LOCAL0|LOG_INFO,"caught signal: %d - exiting",sig);
#endif

	closelog();
	TidyUp();
	_exit(0);
}

/**************************************************************************/
/***************************************************************************

   TermHandler

	Handler for the SIGTERM signal. It cleans up the lock file and
   closes the server's master socket, then immediately exits.

	sig			 I					  the signal number (SIGTERM)

	Returns: none
																									 
***************************************************************************/
/**************************************************************************/

void TermHandler(int sig)
{
	TidyUp();
	_exit(0);
}

/**************************************************************************/
/***************************************************************************

   HupHandler

	Handler for the SIGHUP signal. It sets the gGracefulShutdown and
   gCaughtHupSignal flags. The latter is used to distinguish this from
   catching SIGUSR1. Typically in real-world servers, SIGHUP is used to
   tell the server that it should re-read its configuration file. Many
   important daemons do this, including syslog and xinetd (under Linux).

	sig			 I					  the signal number (SIGTERM)

	Returns: none
																									 
***************************************************************************/
/**************************************************************************/

void HupHandler(int sig)
{
	syslog(LOG_LOCAL0|LOG_INFO,"caught SIGHUP");
	gGracefulShutdown=1;
	gCaughtHupSignal=1;

	/****************************************************************/
	/* perhaps at this point you would re-read a configuration file */
	/****************************************************************/

	return;
}

/**************************************************************************/
/***************************************************************************

   Usr1Handler

	Handler for the SIGUSR1 signal. This sets the gGracefulShutdown flag,
   which permits active connections to run to completion before shutdown.
   It is therefore a more friendly way to shut down the server than 
   sending SIGTERM.

	sig			 I					  the signal number (SIGTERM)

	Returns: none
																									 
***************************************************************************/
/**************************************************************************/

void Usr1Handler(int sig)
{
	syslog(LOG_LOCAL0|LOG_INFO,"caught SIGUSR1 - soft shutdown");
	gGracefulShutdown=1;

	return;
}

/**************************************************************************/
/***************************************************************************

   TidyUp

	Dispose of system resources. This function is not strictly necessary,
   as UNIX processes clean up after themselves (heap memory is freed,
   file descriptors are closed, etc.) but it is good practice to
   explicitly release that which you have allocated.

	Returns: none
																									 
***************************************************************************/
/**************************************************************************/

void TidyUp(void)
{
	if(gLockFileDesc!=-1)
		{
		close(gLockFileDesc);
		unlink(gLockFilePath);
		gLockFileDesc=-1;
		}

	if(gMasterSocket!=-1)
		{
		close(gMasterSocket);
		gMasterSocket=-1;
		}
}
