#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *line = NULL;
  size_t cap = 0;

  while (1) {
    printf("Enter programs to run.\n> ");
    fflush(stdout);

    ssize_t n = getline(&line, &cap, stdin);
    if (n == -1) {
      putchar('\n');
      break;
    }
    if (n > 0 && line[n - 1] == '\n') {
      line[n - 1] = '\0';
    }
    if (line[0] == '\0')
      continue;

    pid_t pid = fork();
    if (pid < 0) {
      perror("fork");
      continue;
    }
    if (pid == 0) {
      execl(line, line, (char *)NULL);
      perror("Exec failure");
      _exit(127);
    } else {
      int status;
      if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
      }
    }
  }

  free(line);
  return 0;
}
