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

//! Function pointer type to overflow handlers, which must match this signature
typedef void (*ALGEA_BOUNDS_OVERFLOW_HANDLER)(const char[] /*!< Message */,
                                              const char[] /*!< File */,
                                              int /*!< Line */);

//! Changes the overflow handler
/*!
  Changes the overflow handler to @p handler, and returns the previous handler
  so as to be able to (re)store it if necessary
  @returns Previous overflow handler
*/
ALGEA_BOUNDS_OVERFLOW_HANDLER ALGEAsetBoundsOverflowHandler(
    ALGEA_BOUNDS_OVERFLOW_HANDLER handler /*!< New overflow handler */);

//! Handle a bounds overflow
void ALGEAhandleBoundsOverflow(
    const char message[] /*!< Message to output to @p stderr */,
    const char file[] /*!< File in which the error occured */,
    int line /*!< Line at which the error occured */);

//! @}
//! @}

#endif // ALGEA_ERRORS_H
