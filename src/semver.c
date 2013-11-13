#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../include/semver.h"

#define SEMVER_VERSION "0.0.0"

/**
 * this is the maximum number of semver specifications the program will accept
 * as arguments
 */
#define MAX_SPECS 1000

void help() {
  printf("semver-c " SEMVER_VERSION "\n");
  printf("\n");
  printf("A C implementation of the http://semver.org/ specification\n");
  printf("Copyright Conrad Pankoff <deoxxa@fknsrs.biz>\n");
  printf("\n");
  printf("This is a very rough clone of node-semver - please see\n");
  printf("https://github.com/isaacs/node-semver for what that is.\n");
  printf("\n");
  printf("Usage: semver-c [options] <version> [<version> [...]]\n");
  printf("Prints valid versions sorted by SemVer precedence\n");
  printf("\n");
  printf("Options:\n");
  printf("-v\n");
  printf("\tPrints out the version number.\n");
  printf("\n");
  printf("-h\n");
  printf("\tThis is the help. You're looking at it.\n");
  printf("\n");
  printf("-r <range>\n");
  printf("\tPrint versions that match the specified range.\n");
  printf("\n");
  printf("-R\n");
  printf("\tPrint versions in reverse order.\n");
  printf("\n");
  printf("Program exits successfully if any valid version satisfies all\n");
  printf("supplied ranges, and prints all satisfying versions.\n");
  printf("\n");
  printf("If no satisfying versions are found, then exits failure.\n");
  printf("\n");
  printf("Versions are printed in order, so supplying multiple versions\n");
  printf("to the utility will just sort them.\n");
}

int main(int argc, char** argv) {
  if (argc == 1) {
    help();
    return 0;
  }

  int spec_count = 0;
  spec_t spec[MAX_SPECS];

  char reverse = 0;
  range_t* range = NULL;

  int c;
  while ((c = getopt(argc, argv, "vhr:R")) != -1) {
    switch (c) {
      case 'v': {
        printf(SEMVER_VERSION "\n");
        return 0;
      }
      case 'h': {
        help();
        return 0;
      }
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
