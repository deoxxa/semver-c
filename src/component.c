#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/semver.h"

void component_init(component_t* component) {
  component->next = NULL;
  component->numeric = 1;
  component->dataRaw = NULL;
  component->dataInt = 0;
}

void component_dump(component_t* component) {
  if (component == NULL) {
    return;
  }

  if (component->numeric == 1) {
    printf("Number: %d\n", component->dataInt);
  } else {
    printf("Text: %s\n", component->dataRaw);
  }

  component_dump(component->next);
}

component_t* component_read(char* str, int len) {
  component_t *head = NULL, *tail = NULL;

  int offset = 0, i = 0, l = 0;
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

    tail->dataRaw = malloc(i - offset);
    strncpy(tail->dataRaw, str + offset, i - offset);

    if (str[i] == '.') {
      i++;
    }

    offset = i;

    l = strlen(tail->dataRaw);
    for (i=0;i<l;i++) {
      if (tail->dataRaw[i] < '0' || tail->dataRaw[i] > '9') {
        tail->numeric = 0;
        break;
      }
    }
    if (tail->numeric) {
      tail->dataInt = strtol(tail->dataRaw, NULL, 10);
    }
  }

  return head;
}

int component_compare(component_t* a, component_t* b) {
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

  int s = strcmp(a->dataRaw, b->dataRaw);

  if (s != 0) {
    return s;
  }

  return component_compare(a->next, b->next);
}
