#ifndef ALGEA_ERRORS_H
#define ALGEA_ERRORS_H

/*! @file
  This file contains the definition for the return codes of non allocation
  functions, and some optional error checking such as bounds checking
  @addtogroup ALGEA
  @{
  @addtogroup errors Errors
  @{
*/

//! All possible return codes for non allocating functions

typedef enum {
  ALGEA_OK = 0,       //!< Function was successful
  ALGEA_ERROR,        //!< Generic error
  ALGEA_DIM_MISMATCH, //!< Argument dimensions aren't compatible
  ALGEA_ALLOC_FAILED, //!< Internal allocation failed (this allocation would
                      //!< never arrive to the user)
} ALGEA_CODES;

//! Handle a bounds overflow
void ALGEAhandleBoundsOverflow(
    const char message[] /*!< Message to output to @p stderr */);

//! @}
//! @}

#endif // ALGEA_ERRORS_H
