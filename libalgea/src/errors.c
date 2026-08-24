#include "algea/errors.h"

#include <stdio.h>
#include <stdlib.h>

void ALGEAhandleBoundsOverflow(const char message[]) {
  fprintf(stderr, "%s", message);
  abort();
}
