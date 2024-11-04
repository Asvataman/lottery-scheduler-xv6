#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

void process_work(int tickets, int process_id) {

    if (settickets(tickets) < 0) {
        printf(1, "Set tickets failed for process %d\n", process_id);
        exit();
    }

    while (1) {
        // Busy loop to keep the process running
    }
}

int main(void) {
    int pid_A, pid_B, pid_C;

    pid_A = fork();
    if (pid_A == 0) {
        process_work(30, 1);
    }

    pid_B = fork();
    if (pid_B == 0) {
        process_work(20, 2);
    }

    pid_C = fork();
    if (pid_C == 0) {
        process_work(10, 3);
    }

    struct pstat stats;
    int total_ticks;

    while (1) {
        if (getpinfo(&stats) == 0) {
            total_ticks = 0;
            int ticks_A = 0, ticks_B = 0, ticks_C = 0,i;

            // get tick counts for each process
            for (i = 0; i < NPROC; i++) {
                if (stats.inuse[i]) {
                    if (stats.pid[i] == pid_A) {
                        ticks_A = stats.ticks[i];
                    } else if (stats.pid[i] == pid_B) {
                        ticks_B = stats.ticks[i];
                    } else if (stats.pid[i] == pid_C) {
                        ticks_C = stats.ticks[i];
                    }
                    total_ticks += stats.ticks[i];
                }
            }

            printf(1, "%d, %d, %d, %d\n", total_ticks, ticks_A, ticks_B, ticks_C);
        } else {
            printf(1, "Error: Could not retrieve process information\n");
            break;
        }

        sleep(100);
    }

    wait();
    wait();
    wait();
    exit();
}
