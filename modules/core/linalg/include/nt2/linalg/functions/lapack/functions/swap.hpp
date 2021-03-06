//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_FUNCTIONS_SWAP_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_FUNCTIONS_SWAP_HPP_INCLUDED

#include <nt2/linalg/functions/swap.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

extern "C"
{
  void NT2_F77NAME(dswap)(  const nt2_la_int* n     , double* dx
                          , const nt2_la_int* incx  , double* dy
                          , const nt2_la_int* incy
                          );

  void NT2_F77NAME(sswap)(  const nt2_la_int* n     , float* dx
                          , const nt2_la_int* incx  , float* dy
                          , const nt2_la_int* incy
                          );

  void NT2_F77NAME(cswap)(  const nt2_la_int* n     , nt2_la_complex* dx
                          , const nt2_la_int* incx  , nt2_la_complex* dy
                          , const nt2_la_int* incy
                          );

  void NT2_F77NAME(zswap)(  const nt2_la_int* n     , nt2_la_complex* dx
                          , const nt2_la_int* incx  , nt2_la_complex* dy
                          , const nt2_la_int* incy
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::swap_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, double_<A1>, S1 >))
                            )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      nt2_la_int ld = a0.leading_size();
      nt2_la_int inc = 1;

      NT2_F77NAME(dswap) ( &ld, a0.raw(), &inc, a1.raw(), &inc);
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::swap_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, single_<A1>, S1 >))
                            )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      nt2_la_int ld = a0.leading_size();
      nt2_la_int inc = 1;

      NT2_F77NAME(sswap) ( &ld, a0.raw(), &inc, a1.raw(), &inc);
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::swap_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, complex_<single_<A1> >, S1 >))
                            )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      nt2_la_int ld = a0.leading_size();
      nt2_la_int inc = 1;

      NT2_F77NAME(cswap) ( &ld, a0.raw(), &inc, a1.raw(), &inc);
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::swap_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, complex_<double_<A1> >, S1 >))
                            )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      nt2_la_int ld = a0.leading_size();
      nt2_la_int inc = 1;

      NT2_F77NAME(zswap) ( &ld, a0.raw(), &inc, a1.raw(), &inc);
    }
  };

} }

#endif
