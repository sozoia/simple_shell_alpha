#ifndef MAIN_H
#define MAIN_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <paths.h>
#include <stdbool.h>
#include <alloca.h>
#include <sys/stat.h>

#define LINEBUF 1024
#define ARGBUF  64
#define DELIMIT " \t\r\n\a"

extern char **environ;
char    *readLine();
char    **parse(char *);
int    execfun(char **);
int    cdfun(char **);
int    exitfun(char **);
char    *_getenv(const char *);
int     _execvp_(const char *, char * const *);


void	free_command(char **arr);
char *getpath(const char *name, char *env[]);
char *_getenv2(char *name, char *env[]);

#define BUILTIN_NUM ((sizeof(builtins)) / (sizeof(builtin)))
#endif