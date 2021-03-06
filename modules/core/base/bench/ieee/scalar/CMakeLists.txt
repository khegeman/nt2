##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  negate.cpp
  sign.cpp
  sbits.cpp
  signnz.cpp
  prev.cpp
  next.cpp
  ulpdist.cpp
  ulp.cpp
  successor.cpp
  predecessor.cpp
  nextpow2.cpp
  nextafter.cpp
  modf.cpp
  minnummag.cpp
  minnum.cpp
  minmag.cpp
  maxnummag.cpp
  maxnum.cpp
  maxmag.cpp
  mantissa.cpp
  ldexp.cpp
  ilogb.cpp
  frexp.cpp
  frac.cpp
  fast_ldexp.cpp
  fast_frexp.cpp
  exponentbits.cpp
  exponent.cpp
  eps.cpp
  copysign.cpp
  bitofsign.cpp
  bitinteger.cpp
  bitfloating.cpp
# List of scalar test files for toolbox ieee
   )

nt2_module_add_tests(core.base.ieee.scalar.bench ${SOURCES})
