#include "best_fit.h"
#include "common.h"
#include <stdio.h>
#include <time.h>

void *best_fit(size_t size) {
  bin_t *curr = CHUNKS->head;
  bin_t *best = NULL;

  while (curr != NULL) {
    if (curr->size >= size) {
      if (best == NULL || curr->size < best->size) {
        best = curr;
      }
    }
    curr = curr->next;
  }

  if (best == NULL) {
    return NULL;
  }

  best->size -= size;
  return best;
}

void best_fit_test(char *chunk_file, char *size_file) {
  printf("Best Fit Tests\n");

  // Izveido brīvo sarakstu no chunk_file un size_file
  CHUNKS = create_free_list(chunk_file);
  SIZES = create_sizes_list(size_file);

  clock_t start = clock();

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

  clock_t end = clock();

  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Izpildes laiks: %.8f sekundes\n", time_spent);
}