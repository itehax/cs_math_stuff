/* Rudimentary example of C std function implementation, K&R */
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>

/* DYNAMIC MEMORY STUFF */

typedef long Align; /* for alignment to long boundary */
union header {      /* block header */
  struct {
    union header *ptr; /* next block if on free list */
    unsigned size;     /* size of this block */
  } s;
  Align x; /* force alignment of blocks */
};
typedef union header Header;

/* FILE STUFF */
#define MY_PERMS 0666
#define MY_NULL 0
#define MY_EOF (-1)
#define MY_BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */
typedef struct _iobuf {
  int cnt;    /* characters left */
  char *ptr;  /* next character position */
  char *base; /* location of buffer */
  int flag;   /* mode of file access */
  int fd;     /* file descriptor */
} MY_FILE;
extern MY_FILE my_iob[OPEN_MAX];
#define my_stdin (&_iob[0])
#define my_stdout (&_iob[1])
#define my_stderr (&_iob[2])
enum _flags {
  _READ = 01,  /* file open for reading */
  _WRITE = 02, /* file open for writing */
  _UNBUF = 04, /* file is unbuffered */
  _EOF = 010,  /* EOF has occurred on this file */
  _ERR = 020   /* error occurred on this file */
};
#define my_c_feof(p) ((p)->flag & _EOF) != 0)
#define my_c_ferror(p) ((p)->flag & _ERR) != 0)
#define my_c_fileno(p) ((p)->fd)
#define my_c_getc(p)                                                           \
  (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define my_c_putc(x, p)                                                        \
  (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define my_c_getchar() getc(stdin)
#define my_c_putcher(x) putc((x), stdout)

void my_printf(const char *fmt, ...);
char *my_fgets(char *s, int n, FILE *iop);
int my_fputs(char *s, FILE *iop);
int my_getline(char *line, int max);
int my_getchar(void);
int _fillbuf(MY_FILE *fp);
MY_FILE *my_fopen(char *name, char *mode);

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(MY_FILE *fp) {
  int bufsize;
  if ((fp->flag & (_READ | _ERR | _EOF)) != _READ)
    return EOF;
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  if (fp->base == NULL) /* no buffer yet */
    if ((fp->base = (char *)malloc(bufsize)) == NULL)
      return EOF; /* can't get buffer */
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) { /* check in case read returns 0 */
    if (fp->cnt == -1)
      fp->flag |= _EOF;
    else
      fp->flag |= _ERR;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char)*fp->ptr++;
}
MY_FILE *my_fopen(char *name, char *mode) {
  int fd;
  MY_FILE *fp;
  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL;
  for (fp = my_iob; fp < my_iob + OPEN_MAX; fp++)
    if ((fp->flag & (_READ | _WRITE)) == 0)
      break;                   /* found free slot */
  if (fp >= my_iob + OPEN_MAX) /* no free slots */
    return NULL;
  if (*mode == 'w')
    fd = creat(name, MY_PERMS);
  else if (*mode == 'a') {
    if ((fd = open(name, O_WRONLY, 0)) == -1)
      fd = creat(name, MY_PERMS);
    lseek(fd, 0L, 2);
  } else
    fd = open(name, O_RDONLY, 0);
  if (fd == -1) /* couldn't access name */
    return NULL;
  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  fp->flag = (*mode == 'r') ? _READ : _WRITE;
  return fp;
}
MY_FILE _iob[OPEN_MAX] = {/* stdin, stdout, stderr */
                          {0, (char *)0, (char *)0, _READ, 0},
                          {0, (char *)0, (char *)0, _WRITE, 1},
                          {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

int main() {
  char buf[1024];
  int n;
  while ((n = read(0, buf, 1024)) > 0) {
    write(1, buf, n);
  }
  return EXIT_SUCCESS;
}

/* get at most n chars from iop */
char *my_fgets(char *s, int n, FILE *iop) {
  register int c;
  register char *cs;

  cs = s;
  while (--n > 0 && (c = getc(iop)) != EOF) {
    if ((*cs++ = c) == '\n') {
      break;
    }
  }
  *cs = '\0';
  return (c == EOF && cs == s) ? NULL : s;
}

int my_getline(char *line, int max) {
  if (fgets(line, max, stdin) == NULL) {
    return 0;
  }
  return strlen(line);
}
/* puts s on file iop */
int my_fputs(char *s, FILE *iop) {
  int c;
  while ((c = *s++)) {
    putc(c, iop);
  }
  return ferror(iop) ? EOF : 0;
}

/* minimal printf, just to test variadics, could do trivially with syscall */
void my_printf(const char *fmt, ...) {
  va_list ap;

  char *sval;
  int ival;
  double dval;

  va_start(ap, fmt); /* points to first unnamed arg */
  for (const char *p = fmt; *p; ++p) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    switch (*++p) {
    case 'd':
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; ++sval) {
        putchar(*sval);
      }
      break;
    default:
      putchar(*p);
      break;
    }
  }
  va_end(ap);
}

/* unbuffered */
int my_getchar(void) {
  char c;
  return (read(0, &c, 1) == 1) ? (unsigned char)c : EOF;
}
