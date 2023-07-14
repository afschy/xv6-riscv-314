#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/pstat.h"
#include "kernel/param.h"
#include "user/user.h"

int main() {
    struct pstat stat;
    int i;

    getpinfo(&stat);
    printf("PID  |  In Use  |  inQ  |  Original Tickets  |  Current Tickets  |  Time Slices\n");
       
    for(i=0; i<NPROC; i++) {
        if(!stat.pid[i]) continue;
        printf("  %d      %d        %d            %d                  %d                 %d\n", 
            stat.pid[i], stat.inuse[i], stat.inQ[i], stat.tickets_original[i], stat.tickets_current[i], stat.time_slices[i]);
    }
    exit(0);
}