#include "common.h"

struct bin {
  size_t size;
  struct bin *next;
};

struct bin *create_free_list(char *chunk_file) {
  struct bin *HEAD = NULL;

  return HEAD;
}

void print_free_list(struct bin *HEAD) {
  struct bin *current = HEAD;
  while (current != NULL) {
    printf("Size: %zu\n", current->size);
    current = current->next;
  }
}
