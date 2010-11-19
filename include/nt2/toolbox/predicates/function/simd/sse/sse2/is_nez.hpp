//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE2_IS_NEZ_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE2_IS_NEZ_HPP_INCLUDED
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for is_nez


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int64_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<is_nez_,tag::simd_(tag::arithmetic_,tag::sse_),int64_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type sctype; 
      typedef typename meta::int32_t_<sctype >::type htype;
      typedef simd::native<htype,tag::sse_> type;
      type tmp1 = is_nez(simd::native_cast<type>(a0));
      const type tmp2 = {_mm_shuffle_epi32(tmp1, _MM_SHUFFLE(2, 3, 0, 1))};
      return simd::native_cast<A0>(b_or(tmp1, tmp2));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<is_nez_,tag::simd_(tag::arithmetic_,tag::sse_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      return is_not_equal(a0,Zero<A0>());
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
