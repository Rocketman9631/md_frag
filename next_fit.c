#include "next_fit.h"
#include "common.h"
#include <stdio.h>
#include <time.h>

/* Next Fit atceras kur notika pedeja atminas pieskirsana un sak meklesanu no
 * tas vietas*/
static bin_t *last = NULL;

void *next_fit(size_t size) {
  void *ptr = NULL;

  if (last == NULL) {
    last = CHUNKS->head;
  }

  bin_t *chunk_curr = last;

  /* Meklē no pēdējās vietas */
  while (chunk_curr != NULL) {
    if (chunk_curr->size >= size) {
      ptr = chunk_curr;
      chunk_curr->size = chunk_curr->size - size;
      if (chunk_curr->size < 0) {
        chunk_curr->size = 0;
      }
      last = chunk_curr; /* atceramies pozīciju */
      return ptr;
    }
    chunk_curr = chunk_curr->next;
  }

  /* ja sasniedzam beigas, sākam no sākuma */
  chunk_curr = CHUNKS->head;
  while (chunk_curr != last) {
    if (chunk_curr->size >= size) {
      ptr = chunk_curr;
      chunk_curr->size = chunk_curr->size - size;
      if (chunk_curr->size < 0) {
        chunk_curr->size = 0;
      }
      last = chunk_curr;
      return ptr;
    }
    chunk_curr = chunk_curr->next;
  }

  return NULL;
}

void next_fit_test(char *chunk_file, char *size_file) {
  printf("Next Fit Tests\n");

  last = NULL; /* pirms testa noliekam vietaa */

  CHUNKS = create_free_list(chunk_file);
  SIZES = create_sizes_list(size_file);

  printf("======= SIZES SARAKSTS =======\n");
  print_free_list(SIZES);
  printf("==============================\n");
  printf("======= CHUNK SARAKSTS =======\n");
  print_free_list(CHUNKS);
  printf("==============================\n");

  clock_t start = clock();
  bin_t *size_curr = SIZES->head;
  while (size_curr != NULL) {
    printf("Rezervē %zu baitus lielu atmiņu... ", size_curr->size);
    if (next_fit(size_curr->size) == NULL) {
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
  printf("========== FRAG TEST=========\n");
  print_frag(CHUNKS);
  printf("==============================\n");
}
