#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../include/semver.h"

/**
 * this is the maximum number of semver specifications the program will accept
 * as arguments
 */
#define MAX_SPECS 1000

int main(int argc, char** argv) {
  int spec_count = 0;
  spec_t spec[MAX_SPECS];

  char reverse = 0;
  range_t* range = NULL;

  int c;
  while ((c = getopt(argc, argv, "r:R")) != -1) {
    switch (c) {
      case 'r': {
        range = range_read(optarg, strlen(optarg));
        break;
      }
      case 'R': {
        reverse = 1;
        break;
      }
    }
  }

  int i;
  for (i=optind;i<argc;++i) {
    spec_init(&spec[spec_count]);

    if (spec_read(&spec[spec_count], argv[i], strlen(argv[i])) == -1) {
      continue;
    }

    if (range && range_compare(range, &spec[spec_count]) != 1) {
      continue;
    }

    spec_count++;
  }

  if (spec_count == 0) {
    return 1;
  }

  if (reverse) {
    qsort(&spec, spec_count, sizeof(spec_t), &spec_compare_qsort_d);
  } else {
    qsort(&spec, spec_count, sizeof(spec_t), &spec_compare_qsort_a);
  }

  for (i=0;i<spec_count;++i) {
    spec_print(&spec[i]);
  }

  return 0;
}
