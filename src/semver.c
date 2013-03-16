#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/semver.h"

void component_init(component_t* component) {
  component->next = NULL;
  component->numeric = 1;
  component->dataRaw = NULL;
  component->dataInt = 0;
}

void component_dump(component_t* component) {
  if (component == NULL) {
    return;
  }

  if (component->numeric == 1) {
    printf("Number: %d\n", component->dataInt);
  } else {
    printf("Text: %s\n", component->dataRaw);
  }

  component_dump(component->next);
}

component_t* component_read(char* str, int len) {
  component_t *head = NULL, *tail = NULL;

  int offset = 0, i = 0, l = 0;
  while (offset < len) {
    if (head == NULL) {
      head = malloc(sizeof(component_t));
      tail = head;
    } else {
      tail->next = malloc(sizeof(component_t));
      tail = tail->next;
    }

    component_init(tail);

    for (i=offset;i<len;++i) {
      if (str[i] == '.') {
        break;
      }
    }

    tail->dataRaw = malloc(i - offset);
    strncpy(tail->dataRaw, str + offset, i - offset);

    if (str[i] == '.') {
      i++;
    }

    offset = i;

    l = strlen(tail->dataRaw);
    for (i=0;i<l;i++) {
      if (tail->dataRaw[i] < '0' || tail->dataRaw[i] > '9') {
        tail->numeric = 0;
        break;
      }
    }
    if (tail->numeric) {
      tail->dataInt = strtol(tail->dataRaw, NULL, 10);
    }
  }

  return head;
}

int component_compare(component_t* a, component_t* b) {
  if (a == NULL && b != NULL) {
    return 1;
  } else if (a != NULL && b == NULL) {
    return -1;
  } else if (a == NULL && b == NULL) {
    return 0;
  }

  if (a->numeric && b->numeric) {
    if (a->dataInt > b->dataInt) {
      return 1;
    } else if (a->dataInt < b->dataInt) {
      return -1;
    }
  }

  int s = strcmp(a->dataRaw, b->dataRaw);

  if (s != 0) {
    return s;
  }

  return component_compare(a->next, b->next);
}

void semver_init(semver_t* semver) {
  semver->major = 0;
  semver->minor = 0;
  semver->patch = 0;
  semver->releaseRaw = NULL;
  semver->buildRaw = NULL;
  semver->release = NULL;
  semver->build = NULL;
}

void semver_dump(semver_t* semver) {
  printf("Major:   %d\n", semver->major);
  printf("Minor:   %d\n", semver->minor);
  printf("Patch:   %d\n", semver->patch);

  printf("Release: (%ld) %s\n", semver->releaseRaw ? strlen(semver->releaseRaw) : 0, semver->releaseRaw);
  component_dump(semver->release);

  printf("Build:   (%ld) %s\n", semver->buildRaw   ? strlen(semver->buildRaw)   : 0, semver->buildRaw);
  component_dump(semver->build);
}

void semver_print(semver_t* semver) {
  printf("%d.%d.%d", semver->major, semver->minor, semver->patch);

  if (semver->releaseRaw) {
    printf("-%s", semver->releaseRaw);
  }

  if (semver->buildRaw) {
    printf("+%s", semver->buildRaw);
  }

  printf("\n");
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
        semver->release = component_read(semver->releaseRaw, strlen(semver->releaseRaw));
        break;
      }

      if (!(str[i] >= '0' && str[i] <= '9') && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z') && str[i] != '-' && str[i] != '.') {
        return -1;
      }
    }
  }

  if (str[o] == '+') {
    l = len - o;
    semver->buildRaw = malloc(l);
    strncpy(semver->buildRaw, &(str[o]) + 1, l - 1);
    o = len;
    semver->build = component_read(semver->buildRaw, strlen(semver->buildRaw));
  }

  return 0;
}

int semver_compare_qsort_a(const void* a, const void* b) {
  return semver_compare(a, b);
}

int semver_compare_qsort_d(const void* a, const void* b) {
  return semver_compare(b, a);
}

int semver_compare(const semver_t* a, const semver_t* b) {
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
