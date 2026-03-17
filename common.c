#include "common.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Globālie mainīgie
 */

linkedlist_t *CHUNKS = NULL;
linkedlist_t *SIZES = NULL;
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

void print_frag(linkedlist_t *free_list) {
  /*
   * External Memory Fragmentation = 1 - (Largest Block Of Free Memory / Total
   * Free Memory)
   * https://en.wikipedia.org/wiki/Fragmentation_(computing)#Comparison
   */

  double external_frag = 0;
  size_t free_memory_largest = 0;
  size_t free_memory_total = 0;

  bin_t *curr = free_list->head;
  while (curr != NULL) {
    if (curr->size > free_memory_largest) {
      free_memory_largest = curr->size;
    }
    free_memory_total += curr->size;
    curr = curr->next;
  }

  external_frag = 1 - ((double)free_memory_largest / (double)free_memory_total);
  printf("Fragmentācija: %f %% \n", external_frag * 100);
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

  // Lasa failu chunks par rindiņai un pievieno tā vērtības
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

  free(line);
  fclose(chunks);
  return free_list;
}

linkedlist_t *create_sizes_list(char *size_file) {
  linkedlist_t *size_list = linkedlist_init();

  FILE *sizes = fopen(size_file, "r");
  if (!sizes) {
    fprintf(stderr, "Nevar atvērt sizes failu %s\n", size_file);
    exit(EXIT_FAILURE);
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  // Lasa failu chunks par rindiņai un pievieno tā vērtības
  while ((read = getline(&line, &len, sizes)) != -1) {
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

    if (size_list->head == NULL) {
      size_list->head = bin;
    } else {
      bin_t *current = size_list->head;
      while (current->next != NULL) {
        current = current->next;
      }
      current->next = bin;
    }

    size_list->length++;
  }
  free(line);
  fclose(sizes);
  return size_list;
}
