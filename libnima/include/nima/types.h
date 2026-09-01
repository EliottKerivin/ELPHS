#ifndef NIMA_TIME_H
#define NIMA_TIME_H

/*!
  @file
  Defines the types used to represent the problem
  @addtogroup nima
  @{
  @addtogroup types Types
  @{
*/

//! Type for counting time
typedef double NIMA_TIME;

//! Type for representing space
typedef double NIMA_SPACE;

//! Type for the function values
typedef _Complex double NIMA_VALUES;

//! Type for equation coefficients
typedef NIMA_VALUES (*NIMA_PDE_COEFFICIENT)(NIMA_SPACE, NIMA_TIME);

//! Type for initial conditions
typedef NIMA_VALUES (*NIMA_INITIAL_CONDITIONS)(NIMA_SPACE);

//! @} Types
//! @} NIMA

#endif // NIMA_TIME_H
