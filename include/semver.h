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
