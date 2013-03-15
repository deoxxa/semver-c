typedef struct semver_s {
  int major;
  int minor;
  int patch;
  char* releaseRaw;
  char* buildRaw;
} semver_t;

void semver_init (semver_t* semver);
void semver_dump (semver_t* semver);
int  semver_read (semver_t* semver, char* str, int len);
void semver_print(semver_t* semver);

int semver_compare        (const semver_t* a, const semver_t* b);
int semver_compare_qsort_a(const void*     a, const void*     b);
int semver_compare_qsort_d(const void*     a, const void*     b);
