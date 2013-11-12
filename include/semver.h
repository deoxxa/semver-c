#ifndef SEMVER_H
#define SEMVER_H

#include <stddef.h>

typedef struct component_s {
  struct component_s* next;
  char numeric;
  size_t dataLen;
  const char* dataRaw;
  int dataInt;
} component_t;

void component_init(component_t* component);
void component_dump(component_t* component);
component_t* component_read(const char* str, size_t len);

int component_compare(component_t* a, component_t* b);

typedef struct spec_s {
  int major;
  int minor;
  int patch;
  size_t releaseLen;
  const char* releaseRaw;
  component_t* release;
  size_t buildLen;
  const char* buildRaw;
  component_t* build;
} spec_t;

void spec_init (spec_t* spec);
void spec_dump (spec_t* spec);
int  spec_read (spec_t* spec, const char* str, size_t len);
void spec_print(spec_t* spec);

int spec_compare        (const spec_t* a, const spec_t* b);
int spec_compare_qsort_a(const void*   a, const void*     b);
int spec_compare_qsort_d(const void*   a, const void*     b);

#endif
