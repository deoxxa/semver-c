#include <string.h>
#include <stdlib.h>

#include "../include/semver.h"

int main(int argc, char** argv) {
  semver_t verify;
  semver_t* semvers = NULL;
  int i, j = 0, count = 0;

  for (i=0;i<argc;++i) {
    semver_init(&verify);
    if (semver_read(&verify, argv[i], strlen(argv[i])) == 0) {
      count++;
    }
  }

  semvers = malloc(count * sizeof(semver_t));

  for (i=0;i<argc;++i) {
    semver_init(&(semvers[j]));
    if (semver_read(&(semvers[j]), argv[i], strlen(argv[i])) == 0) {
      ++j;
    }
  }

  char reverse = 0;
  for (i=0;i<argc;++i) {
    if (strncmp("-r", argv[i], strlen(argv[i])) == 0) {
      reverse = 1;
    }
  }

  if (reverse) {
    qsort(semvers, count, sizeof(semver_t), &semver_compare_qsort_d);
  } else {
    qsort(semvers, count, sizeof(semver_t), &semver_compare_qsort_a);
  }

  for (i=0;i<count;++i) {
    semver_print(&(semvers[i]));
  }

  return 0;
}
