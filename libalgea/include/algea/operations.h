#ifndef ALGEA_OPERATIONS_H
#define ALGEA_OPERATIONS_H

/*!
  @file
  Defines various operations on mixed types
*/

#include "algea/errors.h"

struct ALGEA_TRIDIAGONAL_STRUCT;
struct ALGEA_VECTOR_STRUCT;
ALGEA_CODES ALGEAmultiplyTV(struct ALGEA_VECTOR_STRUCT *out,
                            const struct ALGEA_TRIDIAGONAL_STRUCT *A,
                            const struct ALGEA_VECTOR_STRUCT *v);

#endif // ALGEA_OPERATIONS_H
