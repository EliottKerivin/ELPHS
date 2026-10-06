#ifndef ALGEA_GENERIC_H
#define ALGEA_GENERIC_H

/*!
  @file
  This file defines some convenience macros for certain operations common to all
  types. Refer to the relevant documentation of each type as behavior cannot be
  guaranteed to be homogeneous between each case, and this does nothing but call
  the appropriate functions
*/
#include "algea/matrix.h"
#include "algea/tridiagonal.h"
#include "algea/vector.h"

//! Access elements
/*!
  Accesses an element of the object as a (possibly read-only) lvalue
*/
#define aat(object, ...)                                                       \
  *_Generic((object),                                                          \
      const ALGEA_MATRIX *: ALGEAcmat,                                         \
      ALGEA_MATRIX *: ALGEAmat,                                                \
      const ALGEA_TRIDIAGONAL *: ALGEActat,                                    \
      ALGEA_TRIDIAGONAL *: ALGEAtat,                                           \
      const ALGEA_VECTOR *: ALGEAcvat,                                         \
      ALGEA_VECTOR *: ALGEAvat)((object), __VA_ARGS__)
#endif // ALGEA_GENERIC_H
