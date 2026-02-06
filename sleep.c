// Code from Valigo's Video

#define SYS_write 1
#define SYS_nanosleep 35
#define SYS_exit 60

typedef struct timespec {
  long tv_sec;
  long tv_nsec;
} timespec;

long syscall1(long number, long arg1) {
  long result;
  __asm__ __volatile__("syscall"
                       : "=a"(result)
                       : "a"(number), "D"(arg1)
                       : "rcx", "r11", "memory");
  return result;
}
long syscall2(long number, long arg1, long arg2) {
  long result;
  __asm__ __volatile__("syscall"
                       : "=a"(result)
                       : "a"(number), "D"(arg1), "S"(arg2)
                       : "rcx", "r11", "memory");
  return result;
}
long syscall3(long number, long arg1, long arg2, long arg3) {
  long result;
  __asm__ __volatile__("syscall"
                       : "=a"(result)
                       : "a"(number), "D"(arg1), "S"(arg2), "d"(arg3)
                       : "rcx", "r11", "memory");
  return result;
}

unsigned long slen(char *string) {
  char *cursor = string;
  while (*cursor) {
    cursor++;
  }
  unsigned long result = cursor - string;
  return result;
}
long stol(char *raw_long) {
  long result = 0;

  char *cursor = raw_long;
  while (*cursor >= '0' && *cursor <= '9') {
    result = result * 10 + (*cursor - '0');
    cursor++;
  }

  return result;
}
void print(char *string) { syscall3(SYS_write, 1, (long)string, slen(string)); }
void sleepsec(long seconds) {
  timespec duration = {0};
  duration.tv_sec = seconds;
  syscall2(SYS_nanosleep, (long)&duration, 0);
}

int main(int argc, char *argv[]) {
  // printf("argc: %d, argv[0]: %s, argv[1]: %s\n", argc, argv[0], argv[1]);

  if (argc != 2) {
    print("Usage: sleep [number]\nPause for [number] seconds");
    return 1;
  }

  char *raw_sec = argv[1];
  long sec = stol(raw_sec);

  sleepsec(sec);

  return 0;
}

void exit(int code) {
  syscall1(SYS_exit, code);
  for (;;) {
  }
}

__attribute__((naked)) void _start() {
  __asm__ __volatile__("xor %ebp, %ebp\n"
                       "mov (%rsp), %rdi\n"
                       "lea 8(%rsp), %rsi\n"
                       "and $-16, %rsp\n"
                       "call main\n"
                       "mov %rax, %rdi\n"
                       "call exit\n");
}
