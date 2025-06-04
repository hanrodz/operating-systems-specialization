#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int intended_exit_code = 0;
    if (argc > 1)
    {
        intended_exit_code = argv[1][0] - '0';
        printf("Intended exit code: %d\n", intended_exit_code);
    }
    pid_t child = fork();
    int exit_code;
    if (child > 0)
    {
        // parent branch
        printf("Parent branch:\n- child: %d\n", child);
        pid_t await = wait(&exit_code);
        exit_code = WEXITSTATUS(exit_code);
        printf("Parent branch:\n- child: %d\n- await: %d\n- exit_code: %d\n", child, await, exit_code);
    }
    else if (child == 0)
    {
        // child branch
        sleep(1);
        printf("Child branch:\n- child: %d\n", child);
        exit(intended_exit_code);
    }
}
