#include "worst_fit.h"
#include "common.h"
#include <stdio.h>

void worst_fit_test(char *chunk_file, char *size_file) {
  printf("Worst Fit Tests\n");
  // Izveido brīvo sarakstu no chunk_file  
  linkedlist_t *free_list = create_free_list(chunk_file);
  linkedlist_t *size_list = create_sizes_list(size_file);
}
