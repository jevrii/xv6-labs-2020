#include "kernel/types.h"
#include "user/user.h"

void
primes()
{
  char is_composite[40] = {0};
  int p[2];
  char buf[4];
  pipe(p);

  int n = 0;

  while (1) {
    if (n >= 35)
      break;

    if (n == 0) {
      n = 2;
    }
    printf("prime %d\n", n);

    int i;
    for (i = n*2; i <= 35; i += n)
      is_composite[i] = 1;

    int x = 0;
    for (i = n+1; i <= 35; i++) {
      if (!is_composite[i]) {
        x = i;
        break;
      }
    }

    if (x == 0)
      break;

    if (fork() > 0) {
      buf[0] = x;
      write(p[1], buf, 1);
      wait(0);
      break;
    }
    else {
      read(p[0], buf, sizeof(buf));
      n = buf[0];
    }
  }
}

int
main(int argc, char *argv[])
{
  primes();
  exit(0);
}
