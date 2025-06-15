#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

char* names[] = {"Gamma", "Beta", "Alpha", "Delta"};

void handle_signal(int sig) {
    if (sig == SIGUSR1) printf("Czekam na rozkazy\n");
    else if (sig == SIGUSR2) printf("Rozpoczynam misję\n");
    else if (sig == SIGTERM) {
        printf("Misja zakończona\n");
        exit(0);
    }
}

void start_agents(int count) {
    for (int i = 0; i < count; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            signal(SIGUSR1, handle_signal);
            signal(SIGUSR2, handle_signal);
            signal(SIGTERM, handle_signal);

            printf("%s: Gotowy do misji\n", names[i]);

            char buf[64];
            while (fgets(buf, sizeof(buf), stdin)) {
                if (strncmp(buf, "Identify!", 9) == 0) {
                    printf("My codename is %s\n", names[i]);
                } else if (strncmp(buf, "Status?", 7) == 0) {
                    printf("%s: My PID is: %d\n", names[i], getpid());
                }
            }

            exit(0);
        }
    }
}
