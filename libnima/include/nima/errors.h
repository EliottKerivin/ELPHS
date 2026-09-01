#ifndef NIMA_ERRORS_H
#define NIMA_ERRORS_H

/*! @file
  Defines the various error codes possibly returned by non allocating functions
  @addtogroup nima
  @{
  @defgroup nima-errors Error management
  @{
*/

//! Various return codes of functions
typedef enum NIMA_CODES_ENUM {
  NIMA_OK = 0,           //!< Everything worked
  NIMA_ERROR,            //!< An unspecified error occured
  NIMA_ALLOC_FAILED,     //!< Memory allocation failed
  NIMA_INVALID_ARGUMENT, //!< At least one argument was invalid
  NIMA_INVALID_OUT,      //!< An invalid out parameter was passed
  NIMA_TOO_FINE,         //!< Requested grid size is too fine, causes overflows
} NIMA_CODES;

//! @} errors
//! @} nima

#endif // NIMA_ERRORS_H
