#include <string.h>

#include "../include/semver.h"

int main(int argc, char** argv) {
  spec_t spec;

  if (argc < 2) {
    return -1;
  }

  spec_init(&spec);
  if (spec_read(&spec, argv[1], strlen(argv[1])) != 0) {
    return -1;
  }
  spec_dump(&spec);

  return 0;
}
