typedef struct component_s {
  struct component_s* next;
  char numeric;
  char* dataRaw;
  int dataInt;
} component_t;

void component_init(component_t* component);
void component_dump(component_t* component);
component_t* component_read(char* str, int len);

typedef struct semver_s {
  int major;
  int minor;
  int patch;
  char* releaseRaw;
  char* buildRaw;
  component_t* release;
  component_t* build;
} semver_t;

void semver_init (semver_t* semver);
void semver_dump (semver_t* semver);
int  semver_read (semver_t* semver, char* str, int len);
void semver_print(semver_t* semver);

int semver_compare        (const semver_t* a, const semver_t* b);
int semver_compare_qsort_a(const void*     a, const void*     b);
int semver_compare_qsort_d(const void*     a, const void*     b);
