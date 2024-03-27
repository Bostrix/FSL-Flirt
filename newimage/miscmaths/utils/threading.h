/*! \file threading.h
    \brief Contains declaration of classes/functions useful for multi-threading

    \author Jesper Andersson
    \version 1.0b, Feb., 2022.
*/
//
// threading.h
//
// Jesper Andersson, FMRIB Image Analysis Group
//
// Copyright (C) 2020 University of Oxford
//

#ifndef threading_h
#define threading_h

#include <cstdint>

namespace Utilities {

/****************************************************************//**
*
* \brief This is a class that is used to specify number of threads.
*
* This is a class that is used instead of an int to to specify number
* of threads for functions and/or constructors. It is intended to
* allow for a default value without risk of any ambiguity in the
* function signature.
*
********************************************************************/
struct NoOfThreads
{
  explicit NoOfThreads(int64_t n) : _n(n) {}
  int64_t _n;

};


/**
 * This function can be used to initialise multi-threading for BLAS
 * operations. It is intended to be called at/near the beginning of
 * the main() function of an executable, and must be called before
 * any BLAS routines are invoked.
 *
 * The behaviour of this function depends on which BLAS implementation
 * is in use. Currently, if OpenBLAS is being used, threading is
 * disabled, as the OpenBLAS threading pool can often have a negative
 * effect on performance.
 *
 */
void fsl_init_blas_threading(uint16_t flags=0);

} // End namespace Utilities

#endif // End #ifndef threading_h
