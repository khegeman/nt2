//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_NAN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_NAN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/sdk/config.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Nan generic tag

     Represents the Nan constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Nan, double, 0
                                , 0xFFFFFFFF, 0xFFFFFFFFFFFFFFFFULL
                                );
  }
  /*!
    Generates IEEE Nan (not a number) for floating point types.


    @par Semantic:

    @code
    T r = Nan<T>();
    @endcode

    is similar to:

    @code
    T r = IEEE nan value;
    @endcode

    is similar to:

    @code
    if T is integral
      r = T(0)
    else if T is floating
      r =  IEEE nan value
    @endcode

    All floating point "nan" generated by nt2 are quiet nan with all bits set to 1
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Nan, Nan)
} }

#include <boost/simd/constant/common.hpp>

#endif
