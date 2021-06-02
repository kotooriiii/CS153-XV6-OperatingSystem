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

int main(int argc, char *argv[]) {

    int v = argc;

    printf(1, "%d",sizeof(*argv) / sizeof(*argv[0]));
    printf(1, "%p\n", &v);
    exit();
}
