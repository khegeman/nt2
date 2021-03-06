//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/max.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <boost/simd/sdk/config.hpp>
#include <complex>

#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/mone.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( max_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::max;
  using nt2::tag::max_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vdT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
     NT2_TEST_ULP_EQUAL(nt2::max(vcT(nt2::Inf<vT>(), nt2::Zero<vT>()), vcT(nt2::Inf<vT>(), nt2::Zero<vT>())), vcT(nt2::Inf<vT>(), nt2::Zero<vT>()), 0);
     NT2_TEST_EQUAL(nt2::max(vdT(nt2::Inf<vdT>()),  vcT(nt2::Inf<vT>(), nt2::Zero<vT>())), vcT(nt2::Inf<vT>(), nt2::Zero<vT>()));
     NT2_TEST_EQUAL(nt2::max(vdT(nt2::Inf<vdT>()),   vdT(nt2::Inf<vdT>())),  vdT(nt2::Inf<vdT>() ));
#endif
     NT2_TEST_EQUAL(nt2::max(vcT(nt2::One<vT>(), nt2::Zero<vT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>())), vcT(nt2::One<vT>(),nt2::Zero<vT>()));
     NT2_TEST_EQUAL(nt2::max(vcT(nt2::Zero<vT>(),nt2::Zero<vT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>())), vcT(nt2::Zero<vT>(),nt2::Zero<vT>()));
     NT2_TEST_EQUAL(nt2::max(vcT(nt2::Zero<vT>(),nt2::One<vT>()),  vcT(nt2::One<vT>(),nt2::Zero<vT>())), vcT(nt2::Zero<vT>(),nt2::One<vT>()));
     NT2_TEST_EQUAL(nt2::max(vcT(nt2::One<vT>(), nt2::Zero<vT>()), vcT(nt2::One<vT>(),nt2::Zero<vT>())), vcT(nt2::One<vT>(), nt2::Zero<vT>()));
     NT2_TEST_EQUAL(nt2::max(nt2::One<vdT>(),   nt2::Zero<vcT>()), vcT(nt2::One<vT>(),nt2::Zero<vT>()));
     NT2_TEST_EQUAL(nt2::max(nt2::Zero<vdT>(),  nt2::Zero<vcT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>()));
     NT2_TEST_EQUAL(nt2::max(nt2::Zero<vdT>(),  nt2::One<vcT>()),  vcT(nt2::One<vT>(),nt2::Zero<vT>()));
     NT2_TEST_EQUAL(nt2::max(nt2::One<vdT>(),   nt2::One<vcT>()),  vcT(nt2::One<vT>(),nt2::Zero<vT>()));
     NT2_TEST_EQUAL(nt2::max(nt2::One<vdT>(),   nt2::Zero<vdT>()), vdT(nt2::One<vdT>()));
     NT2_TEST_EQUAL(nt2::max(nt2::Zero<vdT>(),  nt2::Zero<vdT>()), vdT(nt2::Zero<vdT>()));
     NT2_TEST_EQUAL(nt2::max(nt2::Zero<vdT>(),  nt2::One<vdT>()),  vdT(nt2::One<vdT>()));
     NT2_TEST_EQUAL(nt2::max(nt2::One<vdT>(),   nt2::One<vdT>()),  vdT(nt2::One<vdT>()));
     NT2_TEST_EQUAL(nt2::max(nt2::One<vdT>(),   nt2::Mone<vdT>()), vdT(nt2::Mone<vdT>()));
     NT2_TEST_EQUAL(nt2::max(nt2::One<vT>(),    nt2::Mone<vdT>()), vdT(nt2::Mone<vdT>()));
     NT2_TEST_EQUAL(nt2::max(nt2::One<vdT>(),   nt2::Mone<vT>()), vdT(nt2::Mone<vdT>()));

}
