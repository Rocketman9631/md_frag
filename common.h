#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>

struct bin;

struct bin *create_free_list(char *chunk_file);
void print_free_list(struct bin *HEAD);
#endif
