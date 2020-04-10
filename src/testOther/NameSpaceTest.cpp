/*
 * NameSpaceTest.cpp
 *
 *  Created on: 2017年12月29日
 *      Author: chic
 */

#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gtest/gtest.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

static int childFunc(void * hostName) {
    struct utsname uts;

    if (sethostname((char *)hostName, strlen((char *)hostName)) == -1)
        errExit("sethostname");

    if (uname(&uts) == -1)
        errExit("uname");
    printf("uts.nodename in child:  %s\n", uts.nodename);
    sleep(5);
    return 0; /* Terminates child */
}

#define STACK_SIZE (1024 * 1024)    /* Stack size for cloned child */
static char child_stack[STACK_SIZE];

//    ./testOther --gtest_filter=NameSpaceTest.uts
TEST(NameSpaceTest,uts)
{
    pid_t child_pid;
    struct utsname uts;

    char str[10]={"newname"};
    child_pid = clone(childFunc, child_stack + STACK_SIZE, // 传尾指针，因为栈是反着的 Points to start of downwardly growing stack
    CLONE_NEWUTS | SIGCHLD, str);
    if (child_pid == -1)
        errExit("clone");
    printf("PID of child created by clone() is %ld\n", (long) child_pid);

    /* Parent falls through to here */

    sleep(1); /* Give child time to change its hostname */

    if (uname(&uts) == -1)
        errExit("uname");
    printf("uts.nodename in parent: %s\n", uts.nodename);

    if (waitpid(child_pid, NULL, 0) == -1) /* Wait for child */
        errExit("waitpid");
    printf("child has terminated\n");
}

