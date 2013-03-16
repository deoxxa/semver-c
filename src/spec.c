#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/semver.h"

void spec_init(spec_t* spec) {
  spec->major = 0;
  spec->minor = 0;
  spec->patch = 0;
  spec->releaseRaw = NULL;
  spec->buildRaw = NULL;
  spec->release = NULL;
  spec->build = NULL;
}

void spec_dump(spec_t* spec) {
  printf("Major:   %d\n", spec->major);
  printf("Minor:   %d\n", spec->minor);
  printf("Patch:   %d\n", spec->patch);

  printf("Release: (%ld) %s\n", spec->releaseRaw ? strlen(spec->releaseRaw) : 0, spec->releaseRaw);
  component_dump(spec->release);

  printf("Build:   (%ld) %s\n", spec->buildRaw   ? strlen(spec->buildRaw)   : 0, spec->buildRaw);
  component_dump(spec->build);
}

void spec_print(spec_t* spec) {
  printf("%d.%d.%d", spec->major, spec->minor, spec->patch);

  if (spec->releaseRaw) {
    printf("-%s", spec->releaseRaw);
  }

  if (spec->buildRaw) {
    printf("+%s", spec->buildRaw);
  }

  printf("\n");
}

int spec_read(spec_t* spec, char* str, int len) {
  int i = 0, o = 0, l = 0;

  for (;i<=len;++i) {
    if (str[i] == '.') {
      spec->major = strtol(str + o, NULL, 10);
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
      spec->minor = strtol(str + o, NULL, 10);
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
      spec->patch = strtol(str + o, NULL, 10);
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
        spec->releaseRaw = malloc(l);
        strncpy(spec->releaseRaw, str + o + 1, l - 1);
        o = i;
        spec->release = component_read(spec->releaseRaw, strlen(spec->releaseRaw));
        break;
      }

      if (!(str[i] >= '0' && str[i] <= '9') && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z') && str[i] != '-' && str[i] != '.') {
        return -1;
      }
    }
  }

  if (str[o] == '+') {
    l = len - o;
    spec->buildRaw = malloc(l);
    strncpy(spec->buildRaw, &(str[o]) + 1, l - 1);
    o = len;
    spec->build = component_read(spec->buildRaw, strlen(spec->buildRaw));
  }

  return 0;
}

int spec_compare_qsort_a(const void* a, const void* b) {
  return spec_compare(a, b);
}

int spec_compare_qsort_d(const void* a, const void* b) {
  return spec_compare(b, a);
}

int spec_compare(const spec_t* a, const spec_t* b) {
  if (a->major != b->major) {
    return a->major > b->major ? 1 : -1;
  }

  if (a->minor != b->minor) {
    return a->minor > b->minor ? 1 : -1;
  }

  if (a->patch != b->patch) {
    return a->patch > b->patch ? 1 : -1;
  }

  // no release > new release > old release
  if (a->release == NULL && b->release != NULL) {
    return 1;
  }

  if (a->release != NULL && b->release == NULL) {
    return -1;
  }

  if (a->release != NULL || b->release != NULL) {
    int release = component_compare(a->release, b->release);

    if (release != 0) {
      return release;
    }
  }

  // new build > old build > no build
  if (a->build != NULL && b->build == NULL) {
    return 1;
  }

  if (a->build == NULL && b->build != NULL) {
    return -1;
  }

  if (a->build != NULL || b->build != NULL) {
    int build = component_compare(a->build, b->build);

    if (build != 0) {
      return build;
    }
  }

  return 0;
}
