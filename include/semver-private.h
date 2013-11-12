#ifndef SEMVER_PRIVATE_H
#define SEMVER_PRIVATE_H

#include <stddef.h>

long semver_private_strntol(const char* str, size_t len);
void semver_private_print(const char* str, size_t len);

#endif
