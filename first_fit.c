#include "first_fit.h"
#include "common.h"
#include <stdio.h>

void first_fit_test(char *chunk_file, char *size_file) {
  printf("First Fit Tests\n");
  // Izveido brīvo sarakstu no chunk_file un size_file
  linkedlist_t *free_list = create_free_list(chunk_file);
  linkedlist_t *size_list = create_sizes_list(size_file);
  // Apstrādā size_file katru rindu izsaucot first_fit
  //
  // bin_t *curr = free_list->head;
  // while (curr != NULL) {
  //
  //}
}

void *first_fit(size_t size) {
  void *ptr = NULL;
  return ptr;
}
