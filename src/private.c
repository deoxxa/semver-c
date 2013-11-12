#include "../include/semver-private.h"

#include <stdio.h>

long semver_private_strntol(const char* str, size_t len) {
  long r = 0;

  while (str[0] >= '0' && str[0] <= '9' && len--) {
    r = r * 10 + ((str++)[0] - '0');
  }

  return r;
}

void semver_private_print(const char* str, size_t len) {
  size_t i;

  for (i=0;i<len;++i) {
    printf("%c", str[i]);
  }
}
