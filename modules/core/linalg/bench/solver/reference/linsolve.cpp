//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include "../../flops/solve.hpp"
#include "../../flops/lu.hpp"

#include "details.hpp"
#include <boost/fusion/include/at.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/absolute_time.hpp>
#include <nt2/sdk/bench/metric/gflops.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;

template<typename T> struct sgesv_nt2
{
  template<typename Setup>
  sgesv_nt2(Setup const& s)
              :  w(boost::fusion::at_c<1>(s))
              ,  h(boost::fusion::at_c<0>(s))
  {
    a  = nt2::rand(h,w, nt2::meta::as_<T>());
    b  = nt2::rand(h,1, nt2::meta::as_<T>());
    }

  void operator()()
  {
    h1 = h;
    nhrs = w;
    nhrs = nt2::width(b);
    jpvt.resize(nt2::of_size(h1, 1) );

    a1 = a;
    b1 = b;

    NT2_F77NAME(sgesv)( &h1, &nhrs, a1.raw(), &h1, jpvt.raw(), b1.raw(),&h1,&i);
    }

  friend std::ostream& operator<<(std::ostream& os, sgesv_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return h*w; }
  std::size_t flops() const {
    return ((FLOPS_GETRF(h,w)+ FLOPS_DGETRS(h,1)));
  }

private:
  std::size_t w,h;
  nt2_la_int i,h1,w1,nhrs;
  nt2::table<T> a,a1,b,b1;
  nt2::table<nt2_la_int> jpvt;
};

NT2_REGISTER_BENCHMARK_TPL( sgesv_nt2, (float) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< sgesv_nt2<T> > ( 1.
                                , and_( geometric(size_min,size_max,size_step)
                                      , geometric(size_min,size_max,size_step)
                                      )
                                , gflops<stats::median_>()
                                );
}


template<typename T> struct dgesv_nt2
{
  template<typename Setup>
  dgesv_nt2(Setup const& s)
              :  w(boost::fusion::at_c<1>(s))
              ,  h(boost::fusion::at_c<0>(s))
  {
    a  = nt2::rand(h,w, nt2::meta::as_<T>());
    b  = nt2::rand(h,1, nt2::meta::as_<T>());
    }

  void operator()()
  {
    h1 = h;
    nhrs = w;
    nhrs = nt2::width(b);
    jpvt.resize(nt2::of_size(h1, 1) );

    a1 = a;
    b1 = b;

    NT2_F77NAME(dgesv)( &h1, &nhrs, a1.raw(), &h1, jpvt.raw(), b1.raw(),&h1,&i);
    }

  friend std::ostream& operator<<(std::ostream& os, dgesv_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return h*w; }
  std::size_t flops() const {
    return ((FLOPS_GETRF(h,w)+ FLOPS_DGETRS(h,1)));
  }

private:
  std::size_t w,h;
  nt2_la_int i,h1,w1,nhrs;
  nt2::table<T> a,a1,b,b1;
  nt2::table<nt2_la_int> jpvt;
};

NT2_REGISTER_BENCHMARK_TPL( dgesv_nt2, (double) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< dgesv_nt2<T> > ( 1.
                                , and_( geometric(size_min,size_max,size_step)
                                      , geometric(size_min,size_max,size_step)
                                      )
                                , gflops<stats::median_>()
                                );
}


template<typename T> struct dgesvx_nt2
{
  template<typename Setup>
  dgesvx_nt2(Setup const& s)
              :  w(boost::fusion::at_c<1>(s))
              ,  h(boost::fusion::at_c<0>(s))
  {
    a  = nt2::rand(h,w, nt2::meta::as_<T>());
    b  = nt2::rand(h,1, nt2::meta::as_<T>());
    }

  void operator()()
  {
  h1 = h;
  nhrs = w;
  n  = nt2::height(a);
  nhrs = nt2::width(b);
  jpvt.resize(nt2::of_size(h1, 1) );
  x = b;
  char fact  = 'N';
  char trans = 'N';
  char equed = 'N';

  af.resize(nt2::of_size(n,n));
  r.resize(nt2::of_size(n,1));
  c.resize(nt2::of_size(n,1));
  ferr.resize(nt2::of_size(nhrs,1));
  berr.resize(nt2::of_size(nhrs,1));
  work.resize(nt2::of_size(4*n,1));
  iwork.resize(nt2::of_size(n,1));

        NT2_F77NAME(dgesvx)( &fact       , &trans
                           , &h1         , &nhrs
                           , a.raw()     , &h1
                           , af.raw()    , &h1
                           , jpvt.raw()  , &equed
                           , r.raw()     , c.raw()
                           , b.raw()     , &h1
                           , x.raw()     , &h1
                           , &rcond      , ferr.raw()
                           , berr.raw()  , work.raw()
                           , iwork.raw() , &i
                           );
    }

  friend std::ostream& operator<<(std::ostream& os, dgesvx_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return h*w; }
  std::size_t flops() const {
    return ((FLOPS_GETRF(h,w)+ FLOPS_DGETRS(h,1)));
  }

private:
  std::size_t w,h;
  nt2_la_int i,h1,w1,nhrs,n;
  double rcond;
  nt2::table<T> a,a1,b,b1,x,af,r,c,ferr,berr,work;
  nt2::table<nt2_la_int> jpvt,iwork;
};

NT2_REGISTER_BENCHMARK_TPL( dgesvx_nt2, (double) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< dgesvx_nt2<T> > ( 1.
                                , and_( geometric(size_min,size_max,size_step)
                                      , geometric(size_min,size_max,size_step)
                                      )
                                , gflops<stats::median_>()
                                );
}


template<typename T> struct sgesvx_nt2
{
  template<typename Setup>
  sgesvx_nt2(Setup const& s)
              :  w(boost::fusion::at_c<1>(s))
              ,  h(boost::fusion::at_c<0>(s))
  {
    a  = nt2::rand(h,w, nt2::meta::as_<T>());
    b  = nt2::rand(h,1, nt2::meta::as_<T>());
    }

  void operator()()
  {
  h1 = h;
  nhrs = w;
  n  = nt2::height(a);
  nhrs = nt2::width(b);
  jpvt.resize(nt2::of_size(h1, 1) );
  x = b;
  char fact  = 'N';
  char trans = 'N';
  char equed = 'N';

  af.resize(nt2::of_size(n,n));
  r.resize(nt2::of_size(n,1));
  c.resize(nt2::of_size(n,1));
  ferr.resize(nt2::of_size(nhrs,1));
  berr.resize(nt2::of_size(nhrs,1));
  work.resize(nt2::of_size(4*n,1));
  iwork.resize(nt2::of_size(n,1));

        NT2_F77NAME(sgesvx)( &fact       , &trans
                           , &h1         , &nhrs
                           , a.raw()     , &h1
                           , af.raw()    , &h1
                           , jpvt.raw()  , &equed
                           , r.raw()     , c.raw()
                           , b.raw()     , &h1
                           , x.raw()     , &h1
                           , &rcond      , ferr.raw()
                           , berr.raw()  , work.raw()
                           , iwork.raw() , &i
                           );
    }

  friend std::ostream& operator<<(std::ostream& os, sgesvx_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return h*w; }
  std::size_t flops() const {
    return ((FLOPS_GETRF(h,w)+ FLOPS_DGETRS(h,1)));
  }

private:
  std::size_t w,h;
  nt2_la_int i,h1,w1,nhrs,n;
  float rcond;
  nt2::table<T> a,a1,b,b1,x,af,r,c,ferr,berr,work;
  nt2::table<nt2_la_int> jpvt,iwork;
};

NT2_REGISTER_BENCHMARK_TPL( sgesvx_nt2, (float) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< sgesvx_nt2<T> > ( 1.
                                , and_( geometric(size_min,size_max,size_step)
                                      , geometric(size_min,size_max,size_step)
                                      )
                                , gflops<stats::median_>()
                                );
}
