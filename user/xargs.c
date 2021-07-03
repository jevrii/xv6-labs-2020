#include "kernel/types.h"
#include "user/user.h"

void
xargs(int argc, char *argv[])
{
    char cmd[2 + strlen(argv[1])];
    cmd[0] = '/';
    strcpy(cmd+1, argv[1]);
    cmd[2 + strlen(argv[1])-1] = 0;
    argv[1] = cmd;

    char *argv2[argc+1];
    for (int i = 1; i < argc; i++)
        argv2[i-1] = argv[i];

    argv2[argc] = 0;

    char buf[512];
    int n = 1, len = 0;
    while (n > 0) {
        n = read(0, buf+len, 1);
        ++len;
        if (n < 1)
            exit(1);
        if (buf[len-1] == '\n') {
            int pid = 0;
            buf[len-1] = 0;
            pid = fork();
            if (pid > 0) {
                len = 0;
                wait(0);
            }
            if (pid == 0) {
                argv2[argc-1] = buf;
                exec(argv[1], argv2);
                printf("exec error\n");
                exit(0);
            }
        }
    }
}

int
main(int argc, char *argv[])
{
  xargs(argc, argv);
  exit(0);
}
// echo abc"def" | xargs echo bye