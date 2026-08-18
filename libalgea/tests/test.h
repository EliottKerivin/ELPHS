#define test(t)                                                                \
  do {                                                                         \
    if (!(t)) {                                                                \
      fprintf(stderr, "%s (l.%i): %s failed\n", __FILE__, __LINE__, #t);       \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0);
