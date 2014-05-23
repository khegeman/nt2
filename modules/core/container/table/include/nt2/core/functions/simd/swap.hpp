//==============================================================================
//         Copyright 2009 - 2014   LRI UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SIMD_SWAP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SIMD_SWAP_HPP_INCLUDED
#ifndef BOOST_SIMD_NO_SIMD

#include <nt2/core/functions/swap.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/run.hpp>

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>

#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION_IF ( nt2::tag::swap_, boost::simd::tag::simd_
                                , (A0)(A1)
                                , ( boost::simd::meta::
                                    is_vectorizable < typename A0::value_type
                                                    , BOOST_SIMD_DEFAULT_EXTENSION
                                                    >
                                  )
                                , ((ast_<A0,nt2::container::domain>))
                                  ((ast_<A1,nt2::container::domain>))
                                )
  {
    typedef void result_type;

    typedef typename A0::value_type                                 stype;
    typedef boost::simd::native<stype,BOOST_SIMD_DEFAULT_EXTENSION> target_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      BOOST_ASSERT_MSG( numel(a0) == numel(a1)
                      , "Swapping expression with incompatible sizes."
                      );

      static const std::size_t N = boost::simd::meta
                                        ::cardinal_of<target_type>::value;

      std::size_t sz          = numel(a0);
      std::size_t aligned_sz  = sz & ~(N-1);
      std::size_t it          = 0;

      for(std::size_t m=aligned_sz; it != m; it+=N)
      {
        target_type t = nt2::run(a0, it, meta::as_<target_type>());
        nt2::run(a0, it, nt2::run(a1, it, meta::as_<target_type>()));
        nt2::run(a1, it, t);
      }

      for(std::size_t m=sz; it != m; ++it)
      {
        stype t = nt2::run(a0, it, meta::as_<stype>());
        nt2::run(a0, it, nt2::run(a1, it, meta::as_<stype>()));
        nt2::run(a1, it, t);
      }
    }
  };
} }

#endif
#endif
