#include "types.h"
#include "user.h"
int main(int argc, char **argv) {


    setpriority(20);

    int i, j;
    for(i=0; i < 43000; i++)
    {
        __asm("nop");
        for( j=0; j < 43000; j++)
        {
            __asm("nop");
        }

    }


    exit();
}






