#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

// int printf(const char *fmt, ...) {
//   panic("Not implemented");
// }

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  int d;
  char c, *s;
  char *p = out;

  va_start(ap, fmt);
  while (*fmt) {
    if (*fmt != '%') {
      *p++ = *fmt++;
      continue;
    }
    fmt++;
    switch (*fmt) {
      case 's':
        s = va_arg(ap, char *);
        while (*s) {
          *p++ = *s++;
        }
        break;
      case 'd':
        d = va_arg(ap, int);
        if (d < 0) {
          *p++ = '-';
          d = -d;
        }
        char buf[32];
        int i = 0;
        do {
          buf[i++] = d % 10 + '0';
          d /= 10;
        } while (d);
        while (i--) {
          *p++ = buf[i];
        }
        break;
      case 'c':
        c = va_arg(ap, int);
        *p++ = c;
        break;
      default:
        break;
    }
    fmt++;
  }

  *p = '\0';
  va_end(ap);
  return p - out;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
