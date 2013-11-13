#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/semver.h"
#include "../include/semver-private.h"

void component_init(component_t* component) {
  component->next = NULL;
  component->numeric = 1;
  component->dataLen = 0;
  component->dataRaw = NULL;
  component->dataInt = 0;
}

void component_dump(const component_t* component) {
  if (component == NULL) {
    return;
  }

  if (component->numeric == 1) {
    printf("Number: %d\n", component->dataInt);
  } else {
    printf("Text: ");
    semver_private_print(component->dataRaw, component->dataLen);
    printf("\n");
  }

  component_dump(component->next);
}

void component_print(const component_t* component) {
  if (component == NULL) {
    return;
  }

  if (component->numeric == 1) {
    printf("%d", component->dataInt);
  } else {
    semver_private_print(component->dataRaw, component->dataLen);
  }

  if (component->next) {
    printf(".");

    component_print(component->next);
  }
}

component_t* component_read(const char* str, size_t len) {
  component_t *head = NULL, *tail = NULL;

  size_t offset = 0, i = 0, l = 0;
  while (offset < len) {
    if (head == NULL) {
      head = malloc(sizeof(component_t));
      tail = head;
    } else {
      tail->next = malloc(sizeof(component_t));
      tail = tail->next;
    }

    component_init(tail);

    for (i=offset;i<len;++i) {
      if (str[i] == '.') {
        break;
      }
    }

    tail->dataLen = i - offset;
    tail->dataRaw = str + offset;

    if (str[i] == '.') {
      i++;
    }

    offset = i;

    l = tail->dataLen;
    for (i=0;i<l;i++) {
      if (tail->dataRaw[i] < '0' || tail->dataRaw[i] > '9') {
        tail->numeric = 0;
        break;
      }
    }
    if (tail->numeric) {
      tail->dataInt = semver_private_strntol(tail->dataRaw, tail->dataLen);
    }
  }

  return head;
}

int component_compare(const component_t* a, const component_t* b) {
  if (a == NULL && b != NULL) {
    return 1;
  } else if (a != NULL && b == NULL) {
    return -1;
  } else if (a == NULL && b == NULL) {
    return 0;
  }

  if (a->numeric && b->numeric) {
    if (a->dataInt > b->dataInt) {
      return 1;
    } else if (a->dataInt < b->dataInt) {
      return -1;
    }
  }

  int s = memcmp(a->dataRaw, b->dataRaw, a->dataLen > b->dataLen ? a->dataLen : b->dataLen);

  if (s != 0) {
    return s;
  }

  return component_compare(a->next, b->next);
}
