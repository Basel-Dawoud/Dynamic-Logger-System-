#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void set_log_level(const char *level, pid_t pid) {
    int sig;
    if (strcasecmp(level, "error") == 0) {
        sig = SIGUSR1;
    } else if (strcasecmp(level, "warning") == 0) {
        sig = SIGUSR2;
    } else if (strcasecmp(level, "info") == 0) {
        sig = SIGRTMIN;
    } else if (strcasecmp(level, "debug") == 0) {
        sig = SIGRTMAX;
    } else {
        fprintf(stderr, "Invalid log level: %s\n", level);
        return;
    }

    // Send the signal to the logger process
    if (kill(pid, sig) == -1) {
        perror("Error sending signal");
    } else {
        printf("Log level changed to %s\n", level);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <log_level> <pid>\n", argv[0]);
        return 1;
    }

    const char *level = argv[1];
    pid_t pid = atoi(argv[2]);

    set_log_level(level, pid);

    return 0;
}

