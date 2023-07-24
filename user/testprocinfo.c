#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/pstat.h"
#include "kernel/param.h"
#include "user/user.h"

int main() {
    struct pstat stat;
    int i;

    if(getpinfo(&stat) == -1) {
        printf("Fetching info failed\n");
        exit(0);
    }
    printf("PID  |  In Use  |  inQ  |  Original Tickets  |  Current Tickets  |  Time Slices\n");
       
    for(i=0; i<NPROC; i++) {
        if(!stat.pid[i]) continue;
        printf("%d\t  %d\t    %d\t\t%d\t\t\t%d\t\t%d\n", 
            stat.pid[i], stat.inuse[i], stat.inQ[i], stat.tickets_original[i], stat.tickets_current[i], stat.time_slices[i]);
    }
    exit(0);
}