#include "first_fit.h"
#include "common.h"
#include <stdio.h>

void *first_fit(size_t size) {
  void *ptr = NULL;
  bin_t *chunk_curr = CHUNKS->head;
  while (chunk_curr != NULL) {
    if (chunk_curr->size < size) {
      chunk_curr = chunk_curr->next;
    } else {
      ptr = chunk_curr;
      chunk_curr->size = chunk_curr->size - size;

      if (chunk_curr->size < 0) {
        chunk_curr->size = 0;
      }
      break;
    }
  }
  return ptr;
}

void first_fit_test(char *chunk_file, char *size_file) {
  printf("First Fit Tests\n");
  // Izveido brīvo sarakstu no chunk_file un size_file
  CHUNKS = create_free_list(chunk_file);
  SIZES = create_sizes_list(size_file);
  printf("======= SIZES SARAKSTS =======\n");
  print_free_list(SIZES);
  printf("==============================\n");
  printf("======= CHUNK SARAKSTS =======\n");
  print_free_list(CHUNKS);
  printf("==============================\n");

  // Apstrādā size_file katru rindu izsaucot first_fit
  bin_t *size_curr = SIZES->head;
  while (size_curr != NULL) {
    printf("Rezervē %zu baitus lielu atmiņu... ", size_curr->size);
    if (first_fit(size_curr->size) == NULL) {
      printf("Neveiksmīgi\n");
      size_curr = size_curr->next;
      continue;
    }
    printf("Veiksmīgi\n");
    size_curr = size_curr->next;
  }

  printf("======= CHUNK SARAKSTS =======\n");
  print_free_list(CHUNKS);
  printf("==============================\n");
  printf("========== FIRST FIT =========\n");
  print_frag(CHUNKS);
  printf("==============================\n");
}
