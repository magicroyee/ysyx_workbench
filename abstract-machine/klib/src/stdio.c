#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

static int int2buf(char *buf, uint32_t data, char type, int width, char fill_c) {
  int i = 0;
  do {
    switch (type)
    {
    case 'd':
      if ((int32_t)data < 0) {
        buf[i++] = '-';
        data = -(int32_t)data;
      }
      buf[i++] = data % 10 + '0';
      data /= 10;
      break;
    case 'u':
      buf[i++] = data % 10 + '0';
      data /= 10;
      break;
    case 'x':
      buf[i++] = "0123456789abcdef"[data % 16];
      data /= 16;
      break;
    default:
      break;
    }
  } while (data);

  while (i < width) {
    buf[i++] = fill_c;
  }
  
  return i;
}

int printf(const char *fmt, ...) {
  // panic("Not implemented");
  va_list ap;
  va_start(ap, fmt);
  char buf[1024];
  int n = vsprintf(buf, fmt, ap);
  va_end(ap);
  
  putstr(buf);
  // putch('?');
  // putch('\n');
  return n;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  // panic("Not implemented");
  int d;
  uint32_t u;
  char fill_c = ' ';
  int width = 0;
  int i = 0;
  char c, *s;
  char *p = out;
  char buf[32];

  while (*fmt) {
    if (*fmt != '%') {
      fill_c = ' ';
      *p++ = *fmt++;
      continue;
    }
    
    fmt++;
    width = 0;
    fill_c = ' ';

    if (*fmt == '0') {
      fill_c = '0';
      fmt++;
    }
    if (*fmt >= '1' && *fmt <= '9') {
      while (*fmt >= '0' && *fmt <= '9') {
        width = width * 10 + *fmt - '0';
        fmt++;
      }
    }

    switch (*fmt) {
      case 's':
        s = va_arg(ap, char *);
        while (*s) {
          *p++ = *s++;
        }
        break;
      case 'd':
        d = va_arg(ap, uint32_t);
        if (d < 0) {
          *p++ = '-';
          d = -d;
        }
        i = int2buf(buf, d, 'd', width, fill_c);
        while (i--) {
          *p++ = buf[i];
        }
        break;
      case 'u':
        u = va_arg(ap, uint32_t);
        i = int2buf(buf, u, 'u', width, fill_c);
        while (i--) {
          *p++ = buf[i];
        }
        break;
      case 'x':
        u = va_arg(ap, uint32_t);
        i = int2buf(buf, u, 'x', width, fill_c);
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
  return p - out;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  int n = vsprintf(out, fmt, ap);
  va_end(ap);
  return n;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
