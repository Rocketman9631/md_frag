#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
/*
 * Saistītais saraksts
 *
 */
typedef struct bin {
  size_t size;
  struct bin *next;
} bin_t;

typedef struct linkedlist {
  int length;
  bin_t *head;
} linkedlist_t;
/*
 * Globālie mainīgie
 */

extern linkedlist_t *CHUNKS;
extern linkedlist_t *SIZES;

linkedlist_t *linkedlist_init();

/*
 * md_frag funkcijas
 */
linkedlist_t *create_free_list(char *chunk_file);
linkedlist_t *create_sizes_list(char *chunk_file);

void print_free_list(linkedlist_t *free_list);
#endif
