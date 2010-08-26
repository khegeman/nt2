################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for XOP availability
################################################################################
IF( NOT NT2_HAS_XOP_SUPPORT)
TRY_RUN(RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${CMAKE_MODULE_PATH}
        ${CMAKE_MODULE_PATH}/src/cpuid.cpp
        CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${NT2_CURRENT_FLAGS}
        OUTPUT_VARIABLE LOG
        ARGS xop
       )

################################################################################
# If file compiles and run, we're set
################################################################################
IF(${COMPILE_RESULT_VAR})
IF( ${RUN_RESULT_VAR} MATCHES "FAILED_TO_RUN")
  set(XOP_FOUND FALSE)
ELSE()
  set(XOP_FOUND ${RUN_RESULT_VAR})
ENDIF()
ELSE()
  set(XOP_FOUND FALSE)
ENDIF()

IF( ${XOP_FOUND} )
MESSAGE( STATUS "XOP available")
ELSE()
MESSAGE( STATUS "XOP not available")
ENDIF()

ENDIF()
