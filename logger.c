#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

typedef enum {
    LOG_DISABLE = 0,  // No logging
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

LogLevel current_log_level = LOG_DISABLE;

// Function to print messages based on the log level
void log_error(const char *msg) {
    if (current_log_level >= LOG_ERROR) {
        printf("[ERROR] %s\n", msg);
    }
}

void log_warning(const char *msg) {
    if (current_log_level >= LOG_WARNING) {
        printf("[WARNING] %s\n", msg);
    }
}

void log_info(const char *msg) {
    if (current_log_level >= LOG_INFO) {
        printf("[INFO] %s\n", msg);
    }
}

void log_debug(const char *msg) {
    if (current_log_level >= LOG_DEBUG) {
        printf("[DEBUG] %s\n", msg);
    }
}

// Signal handler to change log level
void change_log_level(int signum) {
    if (signum == SIGUSR1) {
        current_log_level = LOG_ERROR;
        printf("Log level changed to ERROR\n");
    } else if (signum == SIGUSR2) {
        current_log_level = LOG_WARNING;
        printf("Log level changed to WARNING\n");
    } else if (signum == SIGRTMIN) {
        current_log_level = LOG_INFO;
        printf("Log level changed to INFO\n");
    } else if (signum == SIGRTMAX) {
        current_log_level = LOG_DEBUG;
        printf("Log level changed to DEBUG\n");
    }
    fflush(stdout);  // Make sure output is immediately printed
}

// Setup signal handling for log level changes
void setup_signal_handling() {
    struct sigaction sa;
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = change_log_level;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction SIGUSR1");
        exit(1);
    }
    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("sigaction SIGUSR2");
        exit(1);
    }
    if (sigaction(SIGRTMIN, &sa, NULL) == -1) {
        perror("sigaction SIGRTMIN");
        exit(1);
    }
    if (sigaction(SIGRTMAX, &sa, NULL) == -1) {
        perror("sigaction SIGRTMAX");
        exit(1);
    }
}

int main() {
    setup_signal_handling();

    // Test logging functionality with the current log level (default is LOG_DISABLE)
    log_error("This is an error message.");
    log_warning("This is a warning message.");
    log_info("This is an info message.");
    log_debug("This is a debug message.");

    // Keep the program running to receive signals and print log messages
    while (1) {
        sleep(1);  // Sleep to wait for signals
    }

    return 0;
}

