#include "best_fit.h"
#include "common.h"
#include <stdio.h>

void *best_fit(size_t size) {
  void *ptr = NULL;
  bin_t *chunk_curr = CHUNKS->head;
  bin_t *best_chunk = NULL;

  while (chunk_curr != NULL) {
    if (chunk_curr->size >= size) {
      if (best_chunk == NULL || chunk_curr->size < best_chunk->size) {
        best_chunk = chunk_curr;
      }
    }
    chunk_curr = chunk_curr->next;
  }

  if (best_chunk != NULL) {
    ptr = best_chunk;
    best_chunk->size = best_chunk->size - size;
  }

  return ptr;
}

void best_fit_test(char *chunk_file, char *size_file) {
  printf("Best Fit Tests\n");

  // Izveido brīvo sarakstu no chunk_file un size_file
  CHUNKS = create_free_list(chunk_file);
  SIZES = create_sizes_list(size_file);

  printf("======= SIZES SARAKSTS =======\n");
  print_free_list(SIZES);
  printf("==============================\n");
  printf("======= CHUNK SARAKSTS =======\n");
  print_free_list(CHUNKS);
  printf("==============================\n");

  // Apstrādā size_file katru rindu izsaucot best_fit
  bin_t *size_curr = SIZES->head;
  while (size_curr != NULL) {
    printf("Rezervē %zu baitus lielu atmiņu... ", size_curr->size);

    if (best_fit(size_curr->size) == NULL) {
      printf("Neveiksmīgi\n");
    } else {
      printf("Veiksmīgi\n");
    }
    size_curr = size_curr->next;
  }

  printf("======= CHUNK SARAKSTS =======\n");
  print_free_list(CHUNKS);
  printf("==============================\n");
}
