#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv) {
    if(argc > 2) {
        printf("Usage: dummyproc [number]\n");
        exit(0);
    }

    if(argc == 2)
        if(settickets(atoi(argv[1])) == -1) {
            printf("Set ticket failed\n");
            exit(0);
        }
    fork();
    while(1);
    exit(0);
}