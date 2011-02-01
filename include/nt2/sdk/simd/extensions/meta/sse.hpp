/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSIONS_META_SSE_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_META_SSE_HPP_INCLUDED

#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/has_key.hpp>
#include <nt2/sdk/config/types.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>

////////////////////////////////////////////////////////////////////////////////
// Tag for SSE extensions
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag { struct sse_ {}; } }

////////////////////////////////////////////////////////////////////////////////
// SSE extensions overload
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, check if it's a SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  is_simd_specific<T,tag::sse_>
        : has_key < set<__m128d, __m128, __m128i>, T > {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  as_simd<T,tag::sse_>
        : boost::mpl::if_ < boost::is_integral<T>
                          , __m128i
                          , typename  boost::mpl
                            ::if_ < boost::is_same<T,float>
                                  , __m128
                                  , typename  boost::mpl
                                    ::if_ < boost::is_same<T,double>
                                        , __m128d
                                        , na_
                                        >::type
                                  >::type
                          >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given SIMD register type, return the associated SIMD extension tag
  //////////////////////////////////////////////////////////////////////////////
  template<class X> struct extension_of<__m128 ,X>  { typedef tag::sse_ type; };
  template<class X> struct extension_of<__m128d,X>  { typedef tag::sse_ type; };
  template<class X> struct extension_of<__m128i,X>  { typedef tag::sse_ type; };
} }

#endif
