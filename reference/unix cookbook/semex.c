/*
 * semex.c --- System V and Linux semaphore exerciser
 *

Copyright (c) 2002, Eric S. Raymond.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:<P>

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.<P>

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.<P>

 *
 * Written sometime in the dark and backward abysm of time back in the 1980s.
 * The 1.2 release in 1994 moved the code to ANSI C with prototypes.
 * The 1.3 release uses strerror(3) rather than its own array of error strings.
 */
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/*
 * This code copied from the semctl(3) man page.
 */
#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
/* union semun is defined by including <sys/sem.h> */
#else
/* according to X/OPEN we have to define it ourselves */
union semun {
      int val;                  /* value for SETVAL */
      struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
      unsigned short *array;    /* array for GETALL, SETALL */
				/* Linux specific part: */
      struct seminfo *__buf;    /* buffer for IPC_INFO */
};
#endif

static ushort	parent;
static int	tty;

static void sigabort(sig)
/* log the occurrence of a signal, die gracefully if it's SIGHUP */
int	sig;	/* the signal number */
{
    (void) printf("Received signal %d\n", sig);
    if (sig == SIGHUP)
	exit(0);
}

void shsemop(semid, sops, nops)
/* perform a semaphore op, announcing the specifics of the operation */
int		semid;
struct sembuf	*sops;
int		nops;
{
    if (tty)
	(void) printf(
		"semop(%d, {%hd, %hd, %hd}, %d) in process %d\n",
		semid, sops->sem_num, sops->sem_op, sops->sem_flg, 
	    nops, getpid());

    nops = semop(semid, sops, nops);

    if (tty)
    {
	/* if we're in the parent, give child processes time to report */
	if (getpid() == parent)
	    (void) sleep(2);

	if (nops == -1)
	    (void) printf("semop in process %d failed: %s\n",
			    getpid(), strerror(errno));
	else
	    (void) printf(
			    "semop in process %d succeeded, returning %d\n",
			    getpid(), nops);
    }
}

main(argc, argv)
int	argc;
char	*argv[];
{
    key_t	    key = IPC_PRIVATE;
    int		    sc, rv, nsems, perms, semflg, semid, semnum = 0;
    struct sembuf   sop;
    char	    cmdline[BUFSIZ], strbuf[BUFSIZ];

    parent = getpid();
    tty = isatty(fileno(stdin));

    for (rv = SIGHUP; rv <= SIGTERM; rv++)
	(void) signal(rv, sigabort);

    if (tty)
    {
	(void) puts("This is the semaphore exerciser, type ? for help");
	(void) printf( "The exerciser process pid is %d\n", parent);
    }

    while ((!tty || fputs("> ", stdout) != EOF) && fgets(cmdline, sizeof(cmdline)-1, stdin))
    {
	errno = 0;

	switch(cmdline[0])
	{
	case 'c':	/* create and select a new semaphore */
	    key = IPC_PRIVATE;
	    nsems = 1;
	    perms = 0660;	/* read & alter by owning user & group */
	    semflg = 0;

	    sc = sscanf(cmdline, "c %ld %d %s %o", &key,&nsems,strbuf,&perms);

	    if (sc >= 3)
	    {
		if (strchr(strbuf, 'c') != (char *)NULL)
		    semflg |= IPC_CREAT;

		if (strchr(strbuf, 'e') != (char *)NULL)
		    semflg |= IPC_EXCL;
	    }
	    semflg |= perms;

	    semid = semget(key, nsems, semflg);
	    if (tty)
	    {
		(void) printf("semget(%ld, %d, %04o) ",	key, nsems, semflg);
		if (semid == -1)
		    (void) printf("failed: %s\n", strerror(errno));
		else
		    (void) printf("succeeded, semid = %d\n", semid);
	    }
	    break;

	case 'f':	/* select a given semaphore group */
	    (void) sscanf(cmdline, "f %d", &semid);
	    (void) printf("Semaphore id %d selected\n", semid);
	    break;

	case 'i':	/* set current semaphore number */
	    (void) sscanf(cmdline, "i %d", &semnum);
	    (void) printf("Semaphore index %d selected\n", semnum);
	    break;

	case 'd':	/* perform a semaphore operation */
	    sc = sscanf(cmdline, "d %hd %s", &sop.sem_op, strbuf);
	    sop.sem_num = semnum;

	    if (sc == 0)
		sop.sem_op = 0;

	    if (sc <= 1)
		sop.sem_flg = 0;

	    if (sc == 2)
	    {
		if (strchr(strbuf, 'u') != (char *)NULL)
		    sop.sem_flg |= SEM_UNDO;

		if (strchr(strbuf, 'n') != (char *)NULL)
		    sop.sem_flg |= IPC_NOWAIT;
	    }

	    if (tty && sop.sem_op < 0)
	    {
		if (rv = fork())	/* parent side */
		{
		    (void) printf("Spawning child with pid = %d\n",rv);
		    (void) sleep(1);
		}		    
		else			/* child side */
		{
		    (void) sleep(1);
		    shsemop(semid, &sop, 1);
		    exit(0);
		}
	    }
	    else
		shsemop(semid, &sop, 1);
	    break;

	case 'v':
	case '\0':
	    (void) sscanf(cmdline, "v %d %d\n", &semid, &semnum);
	    if (tty)
		(void) printf("semctl(%d, %d, GETVAL) returns %d\n",
			semid, semnum, semctl(semid, semnum, GETVAL, NULL));
	    break;

	case 'p':
	    (void) sscanf(cmdline, "p %d %d\n", &semid, &semnum);
	    if (tty)
		(void) printf("semctl(%d, %d, GETPID) returns %d\n",
			semid, semnum, semctl(semid, semnum, GETPID, NULL));
	    break;

	case 'n':
	    (void) sscanf(cmdline, "n %d %d\n", &semid, &semnum);
	    if (tty)
		(void) printf("semctl(%d, %d, GETNCNT) returns %d\n",
			semid, semnum, semctl(semid, semnum, GETNCNT, NULL));
	    break;

	case 'z':
	    (void) sscanf(cmdline, "z %d %d\n", &semid, &semnum);
	    if (tty)
		(void) printf("semctl(%d, %d, GETZCNT) returns %d\n",
			semid, semnum, semctl(semid, semnum, GETZCNT, NULL));
	    break;

	case 's':	/* set the value of a semaphore */
	    {
		union semun semval;

		semval.val = 0;

		(void) sscanf(cmdline, "s %d", &semval.val);

		rv = semctl(semid, semnum, SETVAL, semval);
		if (tty)
		{
		    (void) printf("semctl(%d, %d, SETVAL, %d) ",
					    semid, semnum, semval);
		    if (rv == -1)
			(void) printf("failed: %s\n", strerror(errno));
		    else
			(void) printf("succeeded, returning %d\n", rv);
		}
	    }
	    break;

	case 'm':	/* query-set mode information */
	    {
		int			uid, gid, mode;
		struct semid_ds		ds;

		sc = sscanf(cmdline, "m %d %d %d %o", &semid,&uid,&gid,&mode);

		rv = semctl(semid, semnum, IPC_STAT, &ds);

		/* retrieve and show the existing modes */
		(void) printf("semctl(%d, %d, IPC_STAT, &ds) ", semnum,semid);
		if (rv == -1)
		    (void) printf("failed: %s\n", strerror(errno));
		else
		{
		(void) printf("succeeded, returning %d\n", rv);
		(void) printf("Here is the semaphore group data:\nds = {\n");
		(void) printf("    sem_perm.uid = %d\n", ds.sem_perm.uid);
		(void) printf("    sem_perm.gid = %d\n", ds.sem_perm.gid);
		(void) printf("    sem_perm.mode = %04o\n", ds.sem_perm.mode);
		(void) printf("    sem_nsems = %d\n", ds.sem_nsems);
		(void) printf("    sem_otime = (%ld) %s",
					ds.sem_otime, ctime(&ds.sem_otime));
		(void) printf("    sem_ctime = (%ld) %s}\n",
					ds.sem_ctime, ctime(&ds.sem_ctime));
		}

		/* if two or more arguments were given, set new modes */
		if (sc >= 2)
		{
		    ds.sem_perm.uid = uid;
		    if (sc >= 3)
			ds.sem_perm.gid = gid;
		    if (sc >= 4)
			ds.sem_perm.mode = mode;

		    rv = semctl(semid, semnum, IPC_SET, &ds);
		    if (tty)
		    {
			(void) printf("semctl(%d, %d, IPC_SET, &ds) ",
					semnum, semid);
			if (rv == -1)
			    (void) printf("failed: %s\n", strerror(errno));
			else
			    (void) printf("succeeded, returning %d\n", rv);
		    }
		}
	    }
	    break;

	case 'r':	/* delete an existing semaphore */
	    (void) sscanf(cmdline, "r %d", &semid);

	    rv = semctl(semid, 0, IPC_RMID, NULL);
	    if (tty)
	    {
		(void) printf("semctl(%d, 0, IPC_RMID) ", semid);
		if (rv == -1)
		    (void) printf("failed: %s\n", strerror(errno));
		else
		    (void) printf("succeeded\n");
	    }
	    break;

	case 'l':	/* list status of semaphore groups */
	    (void) system("exec ipcs -sbopt");
	    break;

	case 'x':	/* leave */
	    return(0);

	case '!':	/* escape to a shell */
	    (void) system(cmdline + 1);
	    break;

	case '?':	/* print on-line help */
(void)printf("c(reate) key nsems [ce] perms -- create a semaphore group\n");
(void)printf("f(ind) semid                  -- selectsemaphore group by id\n");
(void)printf("i(ndex) semnum                -- select a semaphore index\n");
(void)printf("d(o) op [un]                  -- do a semaphore operation\n");
(void)printf("v(alue) semid semnum          -- query a semaphore's semval\n");
(void)printf("p(id) semid semnum            -- query a semaphore's sempid\n");
(void)printf("n(cnt) semid semnum           -- query a semaphore's semncnt\n");
(void)printf("z(cnt) semid semnum           -- query a semaphore's semzcnt\n");
(void)printf("m(mask) semid uid gid mode    -- query/set semaphore's mode\n");
(void)printf("r(emove) semid                -- remove a semaphore group\n");
(void)printf("s(et) semval                  -- set given semaphore's value\n");
(void)printf("l(ist)                        -- run ipcs -sbopt\n");
(void)printf("x(it)                         -- exit\n\n");

(void)printf("! cmd                         -- execute a shell command\n");
(void)printf("?                             -- print this help message\n\n");
	    break;

	default:
	    (void)printf("Illegal command -- type ? for help\n");
	    break;
	}

	(void) sleep(1);
    }
    return(0);
}

/* semex.c ends here */
