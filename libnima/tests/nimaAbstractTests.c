#include "nima/abstractProblem.h"
#include "nima/errors.h"
#include "nima/types.h"
#include "test.h"

#include "abstractProblem_internal.h"

#include <stdlib.h>

NIMA_VALUES d(NIMA_SPACE, NIMA_TIME) { return 0; }

int main() {
  NIMA_ABSTRACT_PROBLEM *ap = (NIMA_ABSTRACT_PROBLEM *)1;
  test(NIMAnewAbstractProblem(&ap, nullptr, nullptr, nullptr, nullptr, 0, 1, 0,
                              1, nullptr),
       NIMA_INVALID_OUT);
  ap = nullptr;
  test(NIMAnewAbstractProblem(&ap, nullptr, nullptr, nullptr, nullptr, 0, 0, 0,
                              1, nullptr),
       NIMA_INVALID_ARGUMENT);
  if (ap != nullptr) exit(EXIT_FAILURE);
  test(NIMAnewAbstractProblem(&ap, nullptr, nullptr, nullptr, nullptr, 0, 1, 0,
                              0, nullptr),
       NIMA_INVALID_ARGUMENT);
  if (ap != nullptr) exit(EXIT_FAILURE);
  test(NIMAnewAbstractProblem(&ap, nullptr, nullptr, nullptr, d, 0, 1, 0, 1,
                              nullptr),
       NIMA_OK);
  if (ap->d != d) exit(EXIT_FAILURE);

  NIMAdeleteAbstractProblem(ap);
  exit(EXIT_SUCCESS);
}
