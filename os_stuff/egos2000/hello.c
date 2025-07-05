void terminal_write(const char *str, int len) {
  for (int i = 0; i < len; i++) {
    *(char *)(0x10000000) = str[i];
  }
}
#include <stdarg.h> // for va_start(), va_end() and va_arg()
#include <stdlib.h> // for itoa()
#include <string.h> // for strlen() and strcat()

void format_to_str(char *out, const char *fmt, va_list args) {
  for (out[0] = 0; *fmt != '\0'; fmt++) {
    if (*fmt != '%') {
      strncat(out, fmt, 1);
    } else {
      fmt++;
      if (*fmt == 's') {
        strcat(out, va_arg(args, char *));
      } else if (*fmt == 'd') {
        itoa(va_arg(args, int), out + strlen(out), 10);
      } else if (*fmt == 'c') {
        char *curr_buf = out + strlen(out);
        *curr_buf++ = (char)va_arg(args, int);
        *curr_buf = '\0';
      } else if (*fmt == 'x') {
        itoa(va_arg(args, int), out + strlen(out), 16);
      } else if (*fmt == 'u') {
        utoa(va_arg(args, unsigned), out + strlen(out), 16);
      } else if (*fmt == 'p') {
        utoa(va_arg(args, unsigned), out + strlen(out), 16);
      } else if (*fmt == 'l' && *(fmt + 1) == 'l' &&
                 *(fmt + 2) == 'u') { /* buggy but dont care */
        fmt += 2;
        utoa(va_arg(args, unsigned), out + strlen(out), 16);
        utoa(va_arg(args, unsigned), out + strlen(out), 16);
      }
    }
  }
}
unsigned format_to_str_len(const char *fmt, va_list args) {
  /* overallocate but its normal and not really a waste */
  unsigned format_len = 0;
  while (*fmt++) {
    if (*fmt != '%') {
      ++format_len;
    } else {
      ++format_len;
      if (*fmt == 's') {
        format_len += strlen(va_arg(args, char *));
      } else if (*fmt == 'd') {
        format_len += sizeof(int);
        va_arg(args, int);
      } else if (*fmt == 'c') {
        format_len += sizeof(char);
        va_arg(args, int);
      } else if (*fmt == 'x') {
        format_len += sizeof(int);
        va_arg(args, int);
      } else if (*fmt == 'u') {
        format_len += sizeof(unsigned);
        va_arg(args, unsigned);
      } else if (*fmt == 'p') {
        format_len += sizeof(unsigned);
        va_arg(args, unsigned);
      } else if (*fmt == 'p') {
      } else if (*fmt == 'l' && *(fmt + 1) == 'l' &&
                 *(fmt + 2) == 'u') { /* buggy but dont care */
        fmt += 2;
        format_len += sizeof(unsigned long long) + 2;
        va_arg(args, unsigned long long);
      }
    }
  }
}
int printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  va_list tmp;
  va_copy(tmp, args);
  unsigned int len = format_to_str_len(format, tmp);
  va_end(tmp);
  char *buf = malloc(len);
  format_to_str(buf, format, args);
  va_end(args);
  terminal_write(buf, strlen(buf));
  free(buf);
  return 0;
}

extern char __heap_start, __heap_end;
static char *brk = &__heap_start;
char *_sbrk(int size) {
  if (brk + size > (char *)&__heap_end) {
    terminal_write("_sbrk: heap grows too large\r\n", 29);
    return NULL;
  }

  char *old_brk = brk;
  brk += size;
  return old_brk;
}

int main() {
  char *msg = "Hello, World!\n\r";
  terminal_write(msg, 15);
  printf("%s-%d%s is awesome!\n", "egos", 2000, "ok buggy_");
  printf("%c is character $\n", '$');
  printf("%c is character 0\n", (char)48);
  printf("%x is integer 1234 in hexadecimal\n", 1234);
  printf("%u is the maximum of unsigned int\n", (unsigned int)0xFFFFFFFF);
  printf("%p is the hexadecimal address of the hello-world string\n", msg);
  printf("%llu is the maximum of unsigned long long\n", 0xFFFFFFFFFFFFFFFFULL);
  return 0;
}
