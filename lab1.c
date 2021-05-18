// ------------------------------------------------------------
// steps to reproduce the hello program demo during lab session:
// ------------------------------------------------------------
// 1. Create new file named hello.c inside local copy of xv6 folder. Copy the source code below over.
// 2. Modify local Makefile to include this new user program to let xv6 recognize this new prog.
// add "_hello/" to variable UPROG
// 3. Make sure both hello.c and Makefile modifications are uploaded to remote copy;
// option1 (sync any changed file): tools -> deployment -> automatic upload (always);
// option2 (sync one specific file):
// choose the file to upload in project window -> tools -> deployment -> upload to <name of your deployment>
// 4. In a sledge terminal session:
// (after entering xv6 folder) $ make qemu-nox
// 5. Run new user program with command below:
// (xv6) $ hello

#include "types.h"
#include "user.h"

int main(int argc, char **argv) {

    int pid;

    pid = fork();
    //Two running processes: The parent and child.

    if(pid > 0) //Only grandpa comes in here, grandpa waits for the parent
    {
        int exitCode;
        int pidR = waitpid(pid, &exitCode, 0);
        printf(1, "Grandpa says it's time to sleep! PID: %d, ExitCode: %d, PIDReturn: %d\n", pid, exitCode, pidR);
        exit(0);
    }

    //Child comes down here

    pid = fork();
    //3 running processes: The grandpa, parent and child. but grandpa is stuck on line 28

    //The child comes here
    if(pid == 0)
    {
        printf(1, "I'm the child! PID: %d\n", pid);
    }
    else //The parent comes here
    {
        waitpid(pid, NULL, 0);
        printf(1, "I'm the parent! PID: %d\n", pid);
    }


    exit(1);
}
//    printf(1, "Waitpid Demo Initializing...\n"); // fd=1 means standard output.
//
//    int defValue = -1;
//    int* status = &defValue;
//
//    int pid = fork();
//
//
//    if(pid > 0)
//    while(waitpid(pid, status, 0) == -1);
//
//    if(pid == 0)
//    {
//        printf(1, "hi im the child :)\n"); // fd=1 means standard output.
//        exit(0);
//    }
//
//    printf(1, "Exit status returned is: %d\n", *status); // fd=1 means standard output.
//
//    exit(0);
//}

