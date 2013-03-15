#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/semver.h"

void semver_init(semver_t* semver) {
  semver->major = 0;
  semver->minor = 0;
  semver->patch = 0;
  semver->releaseRaw = NULL;
  semver->buildRaw = NULL;
}

void semver_dump(semver_t* semver) {
  printf("Major:   %d\n", semver->major);
  printf("Minor:   %d\n", semver->minor);
  printf("Patch:   %d\n", semver->patch);
  printf("Release: (%ld) %s\n", semver->releaseRaw ? strlen(semver->releaseRaw) : 0, semver->releaseRaw);
  printf("Build:   (%ld) %s\n", semver->buildRaw   ? strlen(semver->buildRaw)   : 0, semver->buildRaw);
}

int semver_read(semver_t* semver, char* str, int len) {
  int i = 0, o = 0, l = 0;

  for (;i<=len;++i) {
    if (str[i] == '.') {
      semver->major = strtol(str + o, NULL, 10);
      i++;
      o = i;
      break;
    }

    if (str[i] < '0' || str[i] > '9') {
      return -1;
    }
  }

  if (i == len) {
    return -1;
  }

  for (;i<=len;++i) {
    if (str[i] == '.') {
      semver->minor = strtol(str + o, NULL, 10);
      i++;
      o = i;
      break;
    }

    if (str[i] < '0' || str[i] > '9') {
      return -1;
    }
  }

  if (i == len) {
    return -1;
  }

  for (;i<=len;++i) {
    if (str[i] == '-' || str[i] == '+' || i == len) {
      semver->patch = strtol(str + o, NULL, 10);
      o = i;
      break;
    }

    if (str[i] < '0' || str[i] > '9') {
      return -1;
    }
  }

  if (o == len) {
    return 0;
  }

  if (str[o] == '-') {
    for (;i<=len;++i) {
      if (str[i] == '+' || i == len) {
        l = i - o;
        semver->releaseRaw = malloc(l);
        strncpy(semver->releaseRaw, str + o + 1, l - 1);
        o = i;
        break;
      }

      if (!(str[i] >= '0' && str[i] <= '9') && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z') && str[i] != '-') {
        return -1;
      }
    }
  }

  if (str[o] == '+') {
    l = len - o;
    semver->buildRaw = malloc(l);
    strncpy(semver->buildRaw, &(str[o]) + 1, l - 1);
    o = len;
  }

  return 0;
}
