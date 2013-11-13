#include <string.h>
#include <stdlib.h>

#include "../include/semver.h"

int main(int argc, char** argv) {
  spec_t verify;
  spec_t* specs = NULL;
  int i, j = 0, count = 0;
  char reverse = 0;

  for (i=0;i<argc;++i) {
    spec_init(&verify);
    if (spec_read(&verify, argv[i], strlen(argv[i])) == 0) {
      count++;
    }
  }

  specs = malloc(count * sizeof(spec_t));

  for (i=0;i<argc;++i) {
    spec_init(&(specs[j]));
    if (spec_read(&(specs[j]), argv[i], strlen(argv[i])) == 0) {
      ++j;
    }
  }

  for (i=0;i<argc;++i) {
    if (strncmp("-r", argv[i], strlen(argv[i])) == 0) {
      reverse = 1;
    }
  }

  if (reverse) {
    qsort(specs, count, sizeof(spec_t), &spec_compare_qsort_d);
  } else {
    qsort(specs, count, sizeof(spec_t), &spec_compare_qsort_a);
  }

  for (i=0;i<count;++i) {
    spec_print(&(specs[i]));
  }

  return 0;
}
