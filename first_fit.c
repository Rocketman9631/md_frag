#include "first_fit.h"
#include "common.h"
#include <stdio.h>

void first_fit_test(char *chunk_file, char *size_file) {
  printf("First Fit Tests\n");
  // Izveido brīvo sarakstu no chunk_file
  create_free_list(chunk_file);
  // Apstrādā size_file katru rindu izsaucot first_fit
}

void *first_fit(size_t size) {
  void *ptr = NULL;
  return ptr;
}
