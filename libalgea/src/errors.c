#include "algea/errors.h"

#include <stdio.h>
#include <stdlib.h>

void defaultOverflowHandler(const char message[], const char file[], int line) {
  fprintf(stderr, "%s (%s:%i)\n", message, file, line);
  abort();
}
static ALGEA_BOUNDS_OVERFLOW_HANDLER ALGEAoverflowHandler =
    defaultOverflowHandler;

ALGEA_BOUNDS_OVERFLOW_HANDLER ALGEAsetBoundsOverflowHandler(
    ALGEA_BOUNDS_OVERFLOW_HANDLER handler) {
  ALGEA_BOUNDS_OVERFLOW_HANDLER prev = ALGEAoverflowHandler;
  ALGEAoverflowHandler = handler;
  return prev;
}

void ALGEAhandleBoundsOverflow(const char message[],
                               const char file[],
                               int line) {
  ALGEAoverflowHandler(message, file, line);
}
