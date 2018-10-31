#include "apue.h"
#include "../common/setfl.c"

#define BUFFSIZE 4096

int
main(int argc, char *argv[])
{
    int n;
    char buf[BUFFSIZE];

    set_fl(STDOUT_FILENO, O_SYNC);

    while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if(n != write(STDOUT_FILENO, buf, n)) {
            err_sys("write error");
        }
    }

    if(n < 0) {
        err_sys("read error");
    }

    exit(0);
}

