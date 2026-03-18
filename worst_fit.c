#include "worst_fit.h"
#include "common.h"
#include <stdio.h>
#include <time.h>

void *worst_fit(size_t size) {
  void *ptr = NULL;
  bin_t *chunk_curr = CHUNKS->head;
  bin_t *worst_chunk = NULL;

  while (chunk_curr != NULL) {
    if (chunk_curr->size >= size) {
      if (worst_chunk == NULL || chunk_curr->size > worst_chunk->size) {
        worst_chunk = chunk_curr;
      }
    }
    chunk_curr = chunk_curr->next;
  }

  if (worst_chunk != NULL) {
    ptr = worst_chunk;
    worst_chunk->size = worst_chunk->size - size;

    if (worst_chunk->size < 0) {
      worst_chunk->size = 0;
    }
  }

  return ptr;
}

void worst_fit_test(char *chunk_file, char *size_file) {
  printf("Worst Fit Tests\n");
  // Izveido brīvo sarakstu no chunk_file un size_file
  CHUNKS = create_free_list(chunk_file);
  SIZES = create_sizes_list(size_file);
  printf("======= SIZES SARAKSTS =======\n");
  print_free_list(SIZES);
  printf("==============================\n");
  printf("======= CHUNK SARAKSTS =======\n");
  print_free_list(CHUNKS);
  printf("==============================\n");

  // Apstrādā size_file katru rindu izsaucot worst_fit

  clock_t start = clock();

  bin_t *size_curr = SIZES->head;
  while (size_curr != NULL) {
    printf("Rezervē %zu baitus lielu atmiņu... ", size_curr->size);
    if (worst_fit(size_curr->size) == NULL) {
      printf("Neveiksmīgi\n");
      size_curr = size_curr->next;
      continue;
    }
    printf("Veiksmīgi\n");
    size_curr = size_curr->next;
  }

  clock_t end = clock();

  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Izpildes laiks: %.8f sekundes\n", time_spent);

  printf("======= CHUNK SARAKSTS =======\n");
  print_free_list(CHUNKS);
  printf("==============================\n");
  printf("========= WORST FIT ==========\n");
  print_frag(CHUNKS);
  printf("==============================\n");
}