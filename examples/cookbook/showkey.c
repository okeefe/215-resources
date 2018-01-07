/*
 * showkey.c -- display cooked key sequences
 *
Copyright (c) 2002, Eric S. Raymond

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
 * Invoke this (no arguments needed) to see keycap-to-keystrokes mappings.
 *
 * by Eric S. Raymond <esr@snark.thyrsus.com>, 1 Nov 88
 * - fix for little-endian machines (version 1.1), 21 Oct 1996.
 * - cleanup and modern packaging (version 1.2), 1 Aug 2002.
 * - changed to use termios (version 1.3), 26 Aug 2002.
 * - typo fix  (version 1.4) 10 Sep 2004.
 */
#include <stdio.h>
#include <termios.h>
#include <signal.h>

#define META	0x80
#define ESC	0x1b

static char *lowchars[] =
{
    "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
    "BS",  "HT",  "LF",  "VT",  "FF",  "CR",  "SO",  "SI",
    "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",
    "CAN", "EM",  "SUB", "ESC", "FS",  "GS",  "RS",  "US",
    "SP",
};

static int signalled;

static void catcher(const int sig)
{
    signalled = sig;
}

main()
{
    struct termios	cooked, raw;
    unsigned char	c;
    unsigned int	i, timeouts;

    for (i = SIGHUP; i <= SIGPOLL; i++)
	(void) signal(i, catcher);

    // Get the state of the tty 
    (void) tcgetattr(0, &cooked);
    // Make a copy we can mess with
    (void) memcpy(&raw, &cooked, sizeof(struct termios));
    // Turn off echoing, linebuffering, and special-character processing,
    // but not the SIGINT or SIGQUIT keys.
    raw.c_lflag &=~ (ICANON | ECHO);
    // Ship the raw control blts
    (void) tcsetattr(0, TCSANOW, &raw);

    (void) printf("Type any key to see the sequence it sends, ^C to quit.\n");
    signalled = 0;
    while (!signalled)
    {
	int		meta;

	read(0, &c, 1);
	if (meta = (c & META))
	    c &=~ META;

	if (c <= ' ')
	    (void) printf("<%s%s>", meta ? "ALT-" : "", lowchars[c]);
	else if (c == 0x3F)
	    (void) printf("<%sDEL>", meta ? "ALT-" : "");
	else if (meta)
	    (void) printf("<ALT-%c>", c);
	else
	    (void) putchar(c);
	(void) fflush(stdout);
    }

    (void) printf("\nBye...\n");
    // Restore the cooked state
    (void) tcsetattr(0, TCSANOW, &cooked);
}

/* showkey.c ends here */
