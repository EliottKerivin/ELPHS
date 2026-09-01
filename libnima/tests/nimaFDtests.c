#include "FDProblem_internal.h"
#include "nima/FDProblem.h"
#include "nima/abstractProblem.h"
#include "nima/errors.h"
#include "nima/types.h"
#include "test.h"

#include <complex.h>
#include <stdlib.h>

static NIMA_VALUES initialValue = CMPLX(63, -29);

static NIMA_VALUES init(NIMA_SPACE /*x*/) { return initialValue; }

int main() {
  NIMA_ABSTRACT_PROBLEM *ap = nullptr;
  NIMAnewAbstractProblem(&ap, nullptr, nullptr, nullptr, nullptr, 0, 1, 0, 1,
                         init);

  NIMA_FDPROBLEM *fdp = (NIMA_FDPROBLEM *)1;
  test(NIMAnewFDProblem(&fdp, ap, 5, 5), NIMA_INVALID_OUT);
  fdp = nullptr;
  test(NIMAnewFDProblem(&fdp, nullptr, 5, 5), NIMA_INVALID_ARGUMENT);
  test(NIMAnewFDProblem(&fdp, ap, 1, 5), NIMA_INVALID_ARGUMENT);
  test(NIMAnewFDProblem(&fdp, ap, 5, 0), NIMA_INVALID_ARGUMENT);
  test(NIMAnewFDProblem(&fdp, ap, 5, 5), NIMA_OK);

  test(fdp->problem == ap, true);
  test(fdp->spaceStep == 1. / 4, true);
  test(fdp->timeStep == 1. / 5, true);
  test(fdp->initialConditions[4] == initialValue, true);

  NIMAdeleteAbstractProblem(ap);
  exit(EXIT_SUCCESS);
}
