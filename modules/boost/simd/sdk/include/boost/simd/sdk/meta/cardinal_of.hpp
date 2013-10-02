//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_CARDINAL_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_CARDINAL_OF_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>

namespace boost { namespace simd { namespace meta
{
  /*!
    @brief Type cardinal

    Computes the number of element fitting into a register able to store a value
    of type @c T.

    @par Models:

    @metafunction

    @par Semantic:

    For any type @c T, the following code:

    @code
    typedef cardinal_of<T>::type r;
    @endcode

    is equivalent to:

    @code
    typedef mpl::size_t<sizeof(register_of<T>::type)/sizeof(scalar_of<T>::type)> r;
    @endcode

    @usage{cardinal_of.cpp}

    @tparam T Any type
  **/
  template<class T>
  struct  cardinal_of
#if !defined(DOXYGEN_ONLY)
        : boost::mpl::size_t<1>
#endif
  {};

  /// INTERNAL ONLY
  template<class T> struct cardinal_of<T&>      : cardinal_of<T> {};

  /// INTERNAL ONLY
  template<class T> struct cardinal_of<T const> : cardinal_of<T> {};
} } }

#endif
