#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(2, "sleep: should have exactly 1 argument\n");
    exit(1);
  }

  int time;
  time = atoi(argv[1]);

  sleep(time);
  exit(0);
}
