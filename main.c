#include "best_fit.h"
#include "first_fit.h"
#include "next_fit.h"
#include "worst_fit.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Programmas argumentu karodziņi
static unsigned flags = 0;
#define FLAG_C (1u << 1)
#define FLAG_S (1u << 2)

// Pārbauda vai fails ar nosaukum filename eksistē.
bool fileExists(const char *filename);

int main(int argc, char **argv) {

  // Chunks un sizes failu nosaukumi
  char *chunks = NULL;
  char *sizes = NULL;

  if (argc != 5) {
    printf("Lietojums: ./md_frag -c chunks -s sizes\n");
    exit(EXIT_FAILURE);
  }

  // Ievada argumentu apstrāde
  for (size_t i = 0; i < argc; ++i) {
    if (strcmp(argv[i], "-c") == 0) {
      if (!fileExists(argv[i + 1])) {
        fprintf(stderr, "Fails %s neeksistē\n", argv[i + 1]);
        exit(EXIT_FAILURE);
      } else {
        flags |= FLAG_C;
        chunks = argv[i + 1];
        i++;
      }
    } else if (strcmp(argv[i], "-s") == 0) {
      if (!fileExists(argv[i + 1])) {
        fprintf(stderr, "Fails %s neeksistē\n", argv[i + 1]);
        exit(EXIT_FAILURE);
      } else {
        flags |= FLAG_S;
        sizes = argv[i + 1];
        i++;
      }
    }
  }
  // Best fit test
  best_fit_test(chunks, sizes);
  // First fit test
  first_fit_test(chunks, sizes);
  // Next fit test
  next_fit_test(chunks, sizes);
  // Worst fit test
  worst_fit_test(chunks, sizes);

  exit(EXIT_SUCCESS);
}

bool fileExists(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file) {
    fclose(file);
    return true;
  }
  return false;
}
