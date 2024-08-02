//Write a program to demonstrate zombie and orphan process
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t my_pid, child_pid, parent_pid;

    child_pid = fork();
    if (child_pid < 0) {
        printf("\nFork failed, exiting!!\n");
        exit(1);
    }
    if (child_pid == 0) {
        // This is the child process part
        printf("\n[CHILD] This is the child process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[CHILD] My pid is %d\n", my_pid);
        printf("[CHILD] My parent's pid is %d\n", parent_pid);
        printf("[CHILD] Exiting\n");
        exit(0);
    } else {
        // This is the parent process part
        printf("\n[PARENT] This is the parent process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[PARENT] My pid is %d\n", my_pid);
        printf("[PARENT] My parent's pid is %d\n", parent_pid);
        printf("[PARENT] Sleeping for 10 seconds\n");
        sleep(10);

        // Wait for the child process to clean up the zombie
        wait(NULL);

        printf("\n[PARENT] Child process with pid = %d has ended, but still had an entry in the process table.\n", child_pid);
        printf("[PARENT] It was therefore a Zombie process until wait() was called.\n");
    }

    return 0;
}



//Implement SJF Non-preemptive scheduling algorithm by defining process structure.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t my_pid, parent_pid, child_pid;
    child_pid = fork();
    
    if (child_pid < 0) {
        printf("\nFork failed, exiting!!\n");
        exit(1);
    }
    
    if (child_pid == 0) {
        // This is the child process
        printf("\n[CHILD] This is the child process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[CHILD] My pid is %d\n", my_pid);
        printf("[CHILD] My parent's pid is %d\n", parent_pid);
        printf("[CHILD] Sleeping for 10 seconds\n");
        sleep(10);
        parent_pid = getppid();
        printf("\n[CHILD] My parent has ended, so I am an orphan process, adopted by init process (PID: %d)\n", parent_pid);
    } else {
        // This is the parent process part
        printf("\n[PARENT] This is the parent process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[PARENT] My pid is %d\n", my_pid);
        printf("[PARENT] My parent's pid is %d\n", parent_pid);
        printf("[PARENT] Exiting\n");
        exit(0);
    }
    
    return 0;
}
