#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *buff = NULL;
  size_t cap = 0;
  ssize_t nread;

  printf("Please enter some text: ");
  fflush(stdout);

  nread = getline(&buff, &cap, stdin);
  if (nread < 0) {
    perror("getline");
    free(buff);
    return 1;
  }

  printf("Tokens:\n");

  char *saveptr = NULL;
  char *tok = strtok_r(buff, " ", &saveptr);

  while (tok != NULL) {
    printf("  %s\n", tok);
    tok = strtok_r(NULL, " ", &saveptr);
  }

  free(buff);
  return 0;
}
