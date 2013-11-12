#include <string.h>
#include <stdlib.h>

#include "../include/semver.h"

int main(int argc, char** argv) {
  range_t* range = NULL;
  spec_t* spec = NULL;

  if (argc < 2) {
    return -1;
  }

  range = range_read(argv[1], strlen(argv[1]));
  if (range == NULL) {
    return -1;
  }

  int i;
  for (i=2;i<argc;++i) {
    spec = malloc(sizeof(spec_t));
    spec_init(spec);
    spec_read(spec, argv[i], strlen(argv[i]));

    if (range->hasLower && spec_compare(spec, range->lower) < 1 - range->includesLower) {
      continue;
    }

    if (range->hasUpper && spec_compare(spec, range->upper) >= range->includesUpper) {
      continue;
    }

    spec_print(spec);
  }

  return 0;
}
