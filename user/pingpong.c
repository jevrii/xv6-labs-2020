#include "kernel/types.h"
#include "user/user.h"

void
pingpong()
{
  int p1[2];
  int p2[2];
  char buf[512];
  pipe(p1);
  pipe(p2);

  if (fork() == 0) {
    // close(0);
    // dup(p1[0]);
    // close(p1[0]);
    // close(p1[1]);

    int n;
    n = read(p1[0], buf, sizeof(buf));
    if (n >= 1) {
      printf("%d: received ping\n", getpid());
      // close(p2[0]);
      if (write(p2[1], buf, 1) != 1) {
        fprintf(2, "%d: pong write error\n", getpid());
        exit(1);
      }
      // close(p2[1]);
      exit(0);
    }
    else {
      fprintf(2, "%d: ping read error\n", getpid());
      exit(1);
    }
  }
  else {
    // close(p1[0]);
    if (write(p1[1], buf, 1) != 1) {
      fprintf(2, "%d: ping write error\n", getpid());
      exit(1);
    }
    // close(p1[1]);

    // close(0);
    // dup(p2[0]);
    // close(p2[0]);
    // close(p2[1]);

    int n;
    n = read(p2[0], buf, sizeof(buf));
    if (n >= 1) {
      printf("%d: received pong\n", getpid());
      exit(0);
    }
    else {
      fprintf(2, "%d: pong read error\n", getpid());
      exit(1);
    }

  }
}

int
main(int argc, char *argv[])
{
  pingpong();
  exit(0);
}
