#include <stdio.h>
#include <stdlib.h>
#define test(function, expected)                                               \
  do {                                                                         \
    int c;                                                                     \
    if ((c = (function)) != (expected)) {                                      \
      fprintf(stderr, "%s (l.%i): %s failed with code %i\n", __FILE__,         \
              __LINE__, #function, c);                                         \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0);
