##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
#     chol.cpp
#     lu.cpp
#     qr.cpp
     schur_result.cpp
#     symeig_result.cpp
#     geneig_result.cpp
#     balance_result.cpp
     symeig.cpp
     geneig.cpp
#     balance.cpp
   )

nt2_module_add_tests(type.complex.linalg.factorization.unit ${SOURCES})
