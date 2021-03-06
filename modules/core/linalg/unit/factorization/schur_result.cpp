//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - schur_result factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/isulpequal.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

// NT2_TEST_CASE_TPL(schur_result, NT2_REAL_TYPES)
// {
//   using nt2::_;
//   using nt2::tag::factorization::schur_;
//   typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
//   typedef nt2::table<T> t_t;
//   typedef nt2::table<itype_t> it_t;
//   t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
//         + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());
//   //  b(_, 1) = b(_, 3);

//   nt2::details::schur_result<t_t> f(b,'V','N','N');

//   nt2::display("b     ", b);
//   nt2::display("values", f.values());
//   t_t z  = f.z();
//   nt2::display("z    ", z);
//   t_t t = f.t();
//   nt2::display("t    ", t);
//   t_t zz =  mtimes(nt2::mtimes(z, t), nt2::trans(z));
//   NT2_TEST(isulpequal(zz, b, T(16.0)));
// }


NT2_TEST_CASE_TPL(schur_result_2, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::tag::factorization::schur_;
  typedef nt2::table<T, nt2::_2D> t_t;
  t_t c = nt2::ones(2, 2, nt2::meta::as_<T>());
  c(3) = -c(3);
  nt2::details::schur_result<t_t> f(c,'V','N','N');

   nt2::display("c     ", c);
//   nt2::display("values", f.values());
   t_t z  = f.z();
   nt2::display("z    ", z);
   t_t t = f.t();
   nt2::display("t    ", t);
   t_t zz =  nt2::mtimes(nt2::mtimes(z, t), nt2::trans(z));
   NT2_TEST(isulpequal(zz, c, T(16.0)));
}

