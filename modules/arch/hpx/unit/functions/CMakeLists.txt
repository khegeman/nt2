##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  colon.cpp
  linspace.cpp
  ones.cpp
  reshape.cpp
  zeros.cpp
  eye.cpp
  triu.cpp
  tril.cpp
  band.cpp
  tri1u.cpp
  tri1l.cpp
  ric.cpp
  rif.cpp
#  rows.cpp
  transform.cpp
  sum.cpp
  homot.cpp
# List of test files for toolbox core.settings
   )

nt2_module_add_tests(arch.hpx.functions.unit ${SOURCES})
