// Code from Valigo's Video

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long stol(char *raw_long) {
  long result = 0;

  char *cursor = raw_long;
  while (*cursor >= '0' && *cursor <= '9') {
    result = result * 10 + (*cursor - '0');
    cursor++;
  }

  return result;
}

int main(int argc, char *argv[]) {
  printf("argc: %d, argv[0]: %s, argv[1]: %s\n", argc, argv[0], argv[1]);

  if (argc != 2) {
    printf("Usage: sleep [number]\nPause for [number] seconds");
    return 1;
  }

  char *raw_sec = argv[1];
  long sec = stol(raw_sec);

  sleep(sec);

  return EXIT_SUCCESS;
}

__attribute__((naked)) void _start() {
  __asm__ __volatile__("xor %ebp, %ebp\n"
                       "mov (%rsp), %rdi\n"
                       "lea 8(%rsp), %rsi\n"
                       "and $-16, %rsp\n"
                       "call main\n");
}
