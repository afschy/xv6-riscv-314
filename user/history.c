#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/spinlock.h"
#include "kernel/syscall_stat.h"
#include "kernel/syscall.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc > 2){
    fprintf(2, "Usage: %s [system call number]\n", argv[0]);
    exit(1);
  }

  struct syscall_stat stat;
  if(argc > 1) {
    int num = atoi(argv[1]);
    history(num, &stat);
    printf("%d:\tsyscall: %s, #: %d, time: %d\n", num, stat.name, stat.count, stat.time);
    exit(0);
  }

  int i;
  for(i=1; i<NSYSCALL; i++) {
    history(i, &stat);
    printf("%d:\tsyscall: %s, #: %d, time: %d\n", i, stat.name, stat.count, stat.time);
  }

  exit(0);
}
