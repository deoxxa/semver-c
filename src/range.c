#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/semver.h"

void range_init(range_t* range) {
  range->next = NULL;
  range->hasLower = 0;
  range->hasUpper = 0;
  range->includesLower = 0;
  range->includesUpper = 0;
  range->lower = NULL;
  range->upper = NULL;
}

void range_dump(const range_t* range) {
  printf("Has lower: %s\n", range->hasLower ? "yes" : "no");
  printf("Includes lower: %s\n", range->includesLower ? "yes" : "no");
  if (range->hasLower && range->lower != NULL) {
    spec_dump(range->lower);
  }

  printf("Has upper: %s\n", range->hasUpper ? "yes" : "no");
  printf("Includes upper: %s\n", range->includesUpper ? "yes" : "no");
  if (range->hasUpper && range->upper != NULL) {
    spec_dump(range->upper);
  }

  printf("Is final: %s\n", range->next == NULL ? "yes" : "no");
  if (range->next != NULL) {
    range_dump(range->next);
  }
}

range_t* range_read(const char* str, size_t len) {
  int offset = 0;

  range_t *root    = NULL,
          *current = NULL,
          *tail    = NULL;

  int tidle, caret, star_ok;

  while (offset < len) {
    tidle = 0;
    caret = 0;
    star_ok = 1;

    current = malloc(sizeof(range_t));
    range_init(current);

    // skip whitespace
    if (str[offset] == ' ') {
      while (str[offset] == ' ') {
        offset++;
      }
    }

    if (str[offset] == '>') {
      offset++;

      star_ok = 0;

      current->hasLower = 1;
      current->hasUpper = 0;

      if (str[offset] == '=') {
        current->includesLower = 1;

        offset++;
      } else {
        current->includesLower = 0;
      }
    } else if (str[offset] == '<') {
      offset++;

      star_ok = 0;

      current->hasLower = 0;
      current->hasUpper = 1;

      current->includesLower = 0;

      if (str[offset] == '=') {
        current->includesUpper = 1;

        offset++;
      } else {
        current->includesUpper = 0;
      }
    } else if (str[offset] == '~') {
      offset++;

      star_ok = 0;
      tidle = 1;

      current->hasLower = 1;
      current->hasUpper = 1;

      current->includesLower = 1;
      current->includesUpper = 0;
    } else if (str[offset] == '^') {
      offset++;

      star_ok = 0;
      caret = 1;

      current->hasLower = 1;
      current->hasUpper = 1;

      current->includesLower = 1;
      current->includesUpper = 0;
    } else {
      if (str[offset] == '=') {
        offset++;

        star_ok = 0;
      }

      current->hasLower = 1;
      current->hasUpper = 1;

      current->includesLower = 1;
      current->includesUpper = 1;
    }

    if (current->hasLower) {
      current->lower = malloc(sizeof(spec_t));
      spec_init(current->lower);
    }

    if (current->hasUpper) {
      current->upper = malloc(sizeof(spec_t));
      spec_init(current->upper);
    }

    // skip whitespace
    if (str[offset] == ' ') {
      while (str[offset] == ' ') {
        offset++;
      }
    }

    //
    // 1: major
    // 2: minor
    // 3: patch
    //
    char         have[3] = {0, 0, 0};
    unsigned int bits[3] = {0, 0, 0};
    char         star[3] = {0, 0, 0};

    int i, j = 0;
    for (i=offset;i<=len;++i) {
      if (str[i] == '.' || str[i] == ' ' || i == len) {
        have[j] = 1;

        if (str[offset] == 'x' || str[offset] == '*') {
          if (!star_ok) {
            return NULL;
          }

          star[j] = 1;
          current->includesUpper = 0;
        } else {
          bits[j] = strtol(str + offset, NULL, 10);
        }

        j++;

        // skip "." if that's why we're here
        if (i < len && str[i] == '.') {
          i++;
        }

        offset = i;

        // we're done
        if (j == 3) {
          break;
          continue;
        }
      }
    }

    if (current->hasLower && have[2]) {
      current->lower->patch = bits[2];
    }
    if (current->hasUpper && have[2]) {
      current->upper->patch = bits[2];
    }
    if (current->hasLower && have[1]) {
      current->lower->minor = bits[1];
    }
    if (current->hasUpper && have[1]) {
      current->upper->minor = bits[1];
    }
    if (current->hasLower && have[0]) {
      current->lower->major = bits[0];
    }
    if (current->hasUpper && have[0]) {
      current->upper->major = bits[0];
    }

    if (tidle) {
      if (have[2]) {
        current->upper->patch = 0;
        current->upper->minor++;
      } else if (have[1]) {
        current->upper->patch = 0;
        current->upper->minor++;
      } else {
        current->upper->major++;
      }
    } else if (caret) {
      if (current->upper->major > 0) {
        current->upper->patch = 0;
        current->upper->minor = 0;
        current->upper->major++;
      } else if (current->upper->minor > 0) {
        current->upper->patch = 0;
        current->upper->minor++;
      }
    } else if (star[0]) {
      current->hasUpper = 0;
      current->hasLower = 0;
    } else if (star[1]) {
      current->upper->patch = 0;
      current->upper->minor = 0;
      current->upper->major++;
    } else if (star[2]) {
      current->upper->patch = 0;
      current->upper->minor++;
    }

    if (tail != NULL) {
      tail->next = current;
    }

    tail = current;

    if (root == NULL) {
      root = current;
    }
  }

  return root;
}

int range_compare(const range_t* range, const spec_t* spec) {
  const range_t* current = range;

  do {
    if (range_compare_one(current, spec) != 0) {
      return 0;
    }

    current = current->next;
  } while (current != NULL);

  return 1;
}

int range_compare_one(const range_t* range, const spec_t* spec) {
  if (range->hasLower && spec_compare(spec, range->lower) < 1 - range->includesLower) {
    return -1;
  }

  if (range->hasUpper && spec_compare(spec, range->upper) >= range->includesUpper) {
    return 1;
  }

  return 0;
}
