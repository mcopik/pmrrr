/* disnan.f -- translated by f2c (version 20061008) */
#ifndef ODNAN_HPP
#define ODNAN_HPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <assert.h>

#include "odsnan.hpp"

template<typename FloatingType>
int odnan_(FloatingType *din)
{
    /* System generated locals */
    int ret_val;

    /* Local variables */
//    extern int odsnan_(FloatingType *, FloatingType *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DISNAN returns .TRUE. if its argument is NaN, and .FALSE. */
/*  otherwise.  To be replaced by the Fortran 2003 intrinsic in the */
/*  future. */

/*  Arguments */
/*  ========= */

/*  DIN      (input) DOUBLE PRECISION */
/*          Input to test for NaN. */

/*  ===================================================================== */

/*  .. External Functions .. */
/*  .. */
/*  .. Executable Statements .. */
    ret_val = odsnan_(din, din);
    return ret_val;
} /* odnan_ */
#endif