#include <string.h> // untuk strtok, strlen
#include <sys/wait.h> // untuk wait()
// #include <sys/types.h>
#include <stdlib.h> // untuk exit()
#include <stdio.h>
#include <unistd.h>

int main()
{   
    int fd[2], fd_sort[2], fd_head[2];
    pid_t ps, sort, head;
    char ps_output[999], sort_output[999], head_output[999];

    pipe(fd);
    ps = fork();

    if (ps == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        if (execlp("ps", "ps", "aux", NULL) == -1) {
            perror("ps");
        }

        exit(17);
    }
    wait(NULL);
    // read(fd[0], ps_output, sizeof(ps_output));
    // printf("%s\n", ps_output);
    // waitpid(ps, NULL, 0);
    // printf("ps done\n");
    // write(fd[1], ps_output, sizeof(ps_output));

    pipe(fd_sort);
    sort = fork();
    if (sort == 0) {
        dup2(fd[0], STDIN_FILENO);
        dup2(fd_sort[1], STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);
        close(fd_sort[0]);
        close(fd_sort[1]);
        // close(stdin);
        // dup(fd[1]);

        if (execlp("sort", "sort", "-nrk", "3,3", NULL) == -1) {
            perror("sort");
        }
        // if (execlp("echo", "echo", NULL) == -1) {
        //     perror("echo");
        // }
        exit(0);
    }
    close(fd[0]);
    close(fd[1]);

    wait(NULL);

    pipe(fd_head);
    head = fork();
    if (head == 0) {
        dup2(fd_sort[0], STDIN_FILENO);
        // dup2(fd_head[1], STDOUT_FILENO);

        close(fd_sort[0]);
        close(fd_sort[1]);
        close(fd_head[0]);
        close(fd_head[1]);

        if (execlp("head", "head", "-5", NULL) == -1) {
            perror("head");
        }
        // if (execlp("echo", "echo", NULL) == -1) {
        //     perror("echo");
        // }
        exit(0);
    }
    close(fd_sort[0]);
    close(fd_sort[1]);
    wait(NULL);
    return 0;
}
