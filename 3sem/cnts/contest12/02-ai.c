#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
run_command(char *cmd)
{
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        execlp(cmd, cmd, (char *) NULL);
        perror("execlp");
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            return 1;
        } else {
            return 0;
        }
    }
}

int
main(int argc, char *argv[])
{
    int cmd1_success = run_command(argv[1]);
    int cmd2_success = 0;

    if (!cmd1_success) {
        cmd2_success = run_command(argv[2]);
    }

    if (cmd1_success || cmd2_success) {
        if (run_command(argv[3])) {
            exit(0);
        } else {
            exit(1);
        }
    }

    exit(1);
}
