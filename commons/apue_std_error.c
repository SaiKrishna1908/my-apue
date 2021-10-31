#include "apue.h"
#include <errno.h>
#include <stdarg.h>

static void err_doit(int , int ,const char *, va_list);

/*
 * Fatal error related to system call
 * 
 */

void err_sys(const char *x, ...) {

	va_list ap;

	va_start (ap, x);
	err_doit(1, errno, x, ap);
	va_end(ap);
	exit(1);
}

/*
 * print a message and return to caller.
 * Caller specifies "errnoflag".
 */

static void err_doit(int errorflag, int error , const char *fmt, va_list ap) {

	char buf[200];

	vsnprintf(buf, MAXLINE-1, fmt, ap);

	if(errorflag) {
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s", strerror(error));
	}

	strcat(buf,"\n");
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
}
