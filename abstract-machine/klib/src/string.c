#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t len = 0;
  while (s[len] != '\0') {
    len++;
  }
  return len;
}

char *strcpy(char *dst, const char *src) {
  int i = 0;
  while (src[i] != '\0') {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0';
  
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  int i = 0;
  while (dst[i] != '\0') {
    i++;
  }
  int j = 0;
  while (src[j] != '\0') {
    dst[i] = src[j];
    i++;
    j++;
  }
  dst[i] = '\0';

  return dst;
}

int strcmp(const char *s1, const char *s2) {
  int i = 0;
  while (s1[i] != '\0' || s2[i] != '\0') {
    if (s1[i] != s2[i]) {
      return (uint8_t)s1[i] - (uint8_t)s2[i];
    }
    if (s1[i] == '\0' || s2[i] == '\0') {
      return (uint8_t)s1[i] - (uint8_t)s2[i];
    }
    i++;
  }

  return 0;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  for (int i = 0; i < n; i++) {
    ((char *)s)[i] = c;
  }

  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  for (int i = 0; i < n; i++) {
    ((char *)out)[i] = ((char *)in)[i];
  }

  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  for (int i = 0; i < n; i++) {
    if (((uint8_t *)s1)[i] != ((uint8_t *)s2)[i]) {
      return ((uint8_t *)s1)[i] - ((uint8_t *)s2)[i];
    }
  }

  return 0;
}

#endif
