//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/reduce.hpp>
#include <nt2/include/constants/eps.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <complex>
#include <nt2/include/functions/complexify.hpp>

NT2_TEST_CASE_TPL ( reduce0,  NT2_REAL_TYPES)
{

  typedef std::complex<T> cT;
  using nt2::reduce;
  using nt2::tag::reduce_;
  nt2::table<cT> a =  nt2::_(T(1), T(4));
  nt2::table<cT> b =  nt2::_(T(0), T(0), T(3));
  nt2::table<cT> c(nt2::of_size(1, 0));
  NT2_TEST_EQUAL(a, reduce(a));
  NT2_TEST_EQUAL(a, reduce(a, nt2::Eps<T>()));
  NT2_TEST_EQUAL(a, reduce(a, nt2::_));
  NT2_TEST_EQUAL(c, reduce(b));

}


