enum {
  PARSE_STATE_MAJOR = 0,
  PARSE_STATE_MINOR,
  PARSE_STATE_PATCH,
  PARSE_STATE_OTHER,
  PARSE_STATE_TAG,
  PARSE_STATE_BUILD
};

typedef struct semver_s {
  int major;
  int minor;
  int patch;
  char* tag;
  char* build;
} semver_t;

void semver_init(semver_t* semver);
void semver_dump(semver_t* semver);
int  semver_read(semver_t* semver, char* str, int len);
