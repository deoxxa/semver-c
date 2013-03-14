#include <string.h>

#include "../include/semver.h"

int main(int argc, char** argv) {
  semver_t semver;

  if (argc < 2) {
    return -1;
  }

  semver_init(&semver);
  if (semver_read(&semver, argv[1], strlen(argv[1])) != 0) {
    return -1;
  }
  semver_dump(&semver);

  return 0;
}
