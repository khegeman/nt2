/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DETAILS_PREPROCESSOR_HPP_INCLUDED
#define NT2_SDK_DETAILS_PREPROCESSOR_HPP_INCLUDED

#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>

////////////////////////////////////////////////////////////////////////////////
// Some short-cut for frequently used PP macros
// Documentation: http://nt2.lri.fr/sdk/details/preprocessor.html
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Turn a macro into a printable screen for debugging
////////////////////////////////////////////////////////////////////////////////
#define NT2_PP_DEBUG(N) BOOST_PP_STRINGIZE( (N) )

////////////////////////////////////////////////////////////////////////////////
// Enumeration macro for index
////////////////////////////////////////////////////////////////////////////////
#define NT2_PP_INDEX(z,n,t)             n

////////////////////////////////////////////////////////////////////////////////
// Enumeration macro for text
////////////////////////////////////////////////////////////////////////////////
#define NT2_PP_TEXT(z,n,t)              t

////////////////////////////////////////////////////////////////////////////////
// Enumerate v n times
////////////////////////////////////////////////////////////////////////////////
#define NT2_PP_ENUM_VALUE(n,v)          BOOST_PP_ENUM(n,NT2_PP_TEXT,v)

////////////////////////////////////////////////////////////////////////////////
// Enumerate v n-1 times
////////////////////////////////////////////////////////////////////////////////
#define NT2_PP_ENUM_SHIFTED_VALUE(n,v)  BOOST_PP_ENUM_SHIFTED(n,NT2_PP_TEXT,v)

////////////////////////////////////////////////////////////////////////////////
// Programamble include directive
// Documentation: http://nt2.lri.fr/sdk/details/include.html
////////////////////////////////////////////////////////////////////////////////
#define NT2_PP_INCLUDE(Base,File) BOOST_PP_STRINGIZE(Base()File)

#endif
