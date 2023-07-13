#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/pstat.h"
#include "user/user.h"

int main() {
    struct pstat stat;
    getpinfo(&stat);
    exit(0);
}