//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/negatenz.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/mthree.hpp>
#include <boost/simd/include/constants/mtwo.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( negatenz_real,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::negatenz;
  using boost::simd::tag::negatenz_;
  typedef typename boost::dispatch::meta::call<negatenz_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(negatenz(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::Nan<T>(), boost::simd::Zero<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::Nan<T>(), boost::simd::Zero<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::Nan<T>(), boost::simd::One<T>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_TYPE_IS(r_t, wished_r_t);
  NT2_TEST_EQUAL(negatenz(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::One<T>(), boost::simd::Zero<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::Two<T>(), boost::simd::Mthree<T>()), boost::simd::Mtwo<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::Two<T>(), boost::simd::Three<T>()), boost::simd::Two<r_t>());
}

NT2_TEST_CASE_TPL ( negatenz_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::negatenz;
  using boost::simd::tag::negatenz_;
  typedef typename boost::dispatch::meta::call<negatenz_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_TYPE_IS(r_t, wished_r_t);
  NT2_TEST_EQUAL(negatenz(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::One<T>(), boost::simd::Zero<T>()), boost::simd::One<r_t>());
}

NT2_TEST_CASE_TPL ( negatenz_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::negatenz;
  using boost::simd::tag::negatenz_;
  typedef typename boost::dispatch::meta::call<negatenz_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_TYPE_IS(r_t, wished_r_t);
  NT2_TEST_EQUAL(negatenz(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(negatenz(boost::simd::One<T>(), boost::simd::Zero<T>()), boost::simd::One<r_t>());
}
