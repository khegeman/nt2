//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================


//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of boost.simd.arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/arithmetic/include/functions/divround.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<divround_> from boost.simd.arithmetic
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::divround_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;

  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(divround_,(RS(vT,T(-10),T(10)))(RS(vT,T(-10),T(10))))
    }
namespace n2 {
  typedef double T;

  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(divround_,(RS(vT,T(-10),T(10)))(RS(vT,T(-10),T(10))))
    }
namespace n3 {
  typedef boost::simd::uint8_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(divround_,(RS(vT,T(0),T(100)))(RS(vT,T(0),T(100))))
    }
namespace n4 {
  typedef boost::simd::uint16_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(divround_,(RS(vT,T(0),T(100)))(RS(vT,T(0),T(100))))
}
namespace n5 {
  typedef boost::simd::uint32_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(divround_,(RS(vT,T(0),T(100)))(RS(vT,T(0),T(100))))
    }
namespace n6 {
  typedef boost::simd::uint64_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(divround_,(RS(vT,T(0),T(100)))(RS(vT,T(0),T(100))))
    }
namespace n7 {
  typedef boost::simd::int8_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(divround_,(RS(vT,T(-100),T(100)))(RS(vT,T(-100),T(100))))
    }
namespace n8 {
  typedef boost::simd::int16_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(divround_,(RS(vT,T(-100),T(100)))(RS(vT,T(-100),T(100))))
    }
namespace n9 {
  typedef boost::simd::int32_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(divround_,(RS(vT,T(-100),T(100)))(RS(vT,T(-100),T(100))))
    }
namespace n10 {
  typedef boost::simd::int64_t T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(divround_,(RS(vT,T(-100),T(100)))(RS(vT,T(-100),T(100))))
}

#undef RS

