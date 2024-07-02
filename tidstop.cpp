#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int pause_tid(pid_t child_pid){
    printf("Pausing child process using ptrace...\n");
    printf("Attaching to process %d...\n", child_pid);
    if (ptrace(PTRACE_SEIZE, child_pid, NULL, NULL) == -1) {
        perror("ptrace seize");
        return 1;
    }

    if (ptrace(PTRACE_INTERRUPT, child_pid, NULL, NULL) == -1) {
        perror("ptrace interrupt");
        exit(1);
    }

    printf("Child %d process paused successfully.\n", child_pid);
    return 0;
}

int main(int argc, char** argv) {

    for(int i=1; i<argc; ++i){
        pid_t child_pid = atoi(argv[i]);
        pause_tid(child_pid);
    }

    printf("Press Enter");
    getchar();

    return 0;
}
