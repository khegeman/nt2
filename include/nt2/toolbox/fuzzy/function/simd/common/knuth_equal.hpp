//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_SIMD_COMMON_KNUTH_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_SIMD_COMMON_KNUTH_EQUAL_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/maxnummag.hpp>
#include <nt2/include/functions/dist.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/ldexp.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for knuth_equal

  /////////////////////////////////////////////////////////////////////////////
  // Compute knuth_equal(const A0& a0, const A0& a1, const A0& a2)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<knuth_equal_,tag::simd_(tag::arithmetic_,Extension),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(3)
    {
      return b_or( iseq(a0, a1)
                   , isle( dist(a0, a1)
			   , ldexp(a2,
				   exponent(maxnummag(a0, a1))
				   )
			   )
                   );
    }

  };
} }

#endif
/// Revised by jt the 15/11/2010
