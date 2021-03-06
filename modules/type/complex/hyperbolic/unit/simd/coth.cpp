//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/coth.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <complex>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mzero.hpp>



NT2_TEST_CASE_TPL ( coth_real__1_0, NT2_SIMD_REAL_TYPES)
{

  using nt2::coth;
  using nt2::tag::coth_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                cT;
  typedef native<T,ext_t>                vT;
  typedef native<cT,ext_t>              cvT;
  typedef typename nt2::meta::call<coth_(cvT)>::type r_t;


  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::coth(nt2::One<cvT>()  ),              nt2::splat<cvT>(nt2::coth(nt2::One<cT>()))  , 2.00);
  NT2_TEST_ULP_EQUAL(nt2::coth(nt2::Zero<cvT>() ),              nt2::splat<cvT>(nt2::coth(nt2::Zero<cT>())) , 2.00);
  NT2_TEST_ULP_EQUAL(nt2::coth(nt2::Mzero<cvT>()),              nt2::splat<cvT>(nt2::coth(nt2::Mzero<cT>())), 2.00);
  NT2_TEST_ULP_EQUAL(nt2::coth(nt2::splat<cvT>(cT(0.5, -0.5))), nt2::splat<cvT>(nt2::coth(cT(0.5, -0.5)))   , 2.00);
  NT2_TEST_ULP_EQUAL(nt2::coth(nt2::splat<cvT>(cT(1, 1))),      nt2::splat<cvT>(nt2::coth(cT(1, 1)))        , 2.00);
  NT2_TEST_ULP_EQUAL(nt2::coth(nt2::splat<cvT>(cT(1, 10))),     nt2::splat<cvT>(nt2::coth(cT(1, 10)))       , 2.00);
  NT2_TEST_ULP_EQUAL(nt2::coth(nt2::splat<cvT>(cT(10, 10))),    nt2::splat<cvT>(nt2::coth(cT(10, 10)))      , 2.00);
  NT2_TEST_ULP_EQUAL(nt2::coth(nt2::splat<cvT>(cT(10, 1))),     nt2::splat<cvT>(nt2::coth(cT(10, 1)))       , 2.00);
} // end of test for floating_

