#include "common.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Saistītais saraksts
 */
linkedlist_t *linkedlist_init() {
  linkedlist_t *list = malloc(sizeof(linkedlist_t));

  if (list == NULL) {
    return NULL;
  }

  list->length = 0;
  list->head = NULL;
  return list;
}

void print_free_list(linkedlist_t *free_list) {
  bin_t *current = free_list->head;

  if (current == NULL) {
    printf("HEAD -> NULL");
    return;
  } else {
    printf("HEAD -> ");
  }
  while (current != NULL) {
    printf("%zu -> ", current->size);
    current = current->next;
  }
  printf("NULL\n");
}

/*
 * md_frag funkcijas
 */

linkedlist_t *create_free_list(char *chunk_file) {
  linkedlist_t *free_list = linkedlist_init();

  FILE *chunks = fopen(chunk_file, "r");
  if (!chunks) {
    fprintf(stderr, "Nevar atvērt chunks failu %s\n", chunk_file);
    exit(EXIT_FAILURE);
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  // Lasta failu chunks par rindiņai un pievieno tā
  while ((read = getline(&line, &len, chunks)) != -1) {
    char *end;
    size_t value = strtol(line, &end, 10);

    if (end == line) {
      fprintf(stderr, "Nepareizs skaitlis: %s", line);
      continue;
    }

    // Pievieno rindas vērtību sarakstam
    bin_t *bin = NULL;
    bin = malloc(sizeof(bin_t));

    if (!bin) {
      fprintf(stderr, "Malloc kļūme!");
    }
    bin->size = value;
    bin->next = NULL;

    if (free_list->head == NULL) {
      free_list->head = bin;
    } else {
      bin_t *current = free_list->head;
      while (current->next != NULL) {
        current = current->next;
      }
      current->next = bin;
    }

    free_list->length++;
  }

  print_free_list(free_list);

  free(line);
  fclose(chunks);
  return free_list;
}
