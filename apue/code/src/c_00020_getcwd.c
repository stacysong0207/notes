#include "apue.h"
#include "c_00002_pathname.c"

int
main(void)
{
    char *ptr;
    size_t size;
    if (chdir("/home/stanley/Downloads/") < 0) {
        err_sys("chdir failed");
    }
    ptr = path_alloc(&size); /* our own function */
    if (getcwd(ptr, size) == NULL) {
        err_sys("getcwd failed");
    }
    printf("cwd = %s\n", ptr);

    exit(0);
}
