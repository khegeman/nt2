//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MAGMA_MCSNE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MAGMA_MCSNE_HPP_INCLUDED

#if defined(NT2_USE_MAGMA)

#include <nt2/linalg/functions/mcsne.hpp>
#include <nt2/sdk/magma/magma.hpp>
#include <nt2/linalg/details/magma_buffer.hpp>
#include <nt2/include/functions/lange.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/trsm.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/maximum.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/include/constants/eps.hpp>


#include <nt2/core/container/table/table.hpp>
#include <magma.h>
#include <nt2/core/container/table/table.hpp>

// namespace nt2{ namespace ext
// {
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mcsne_, nt2::tag::magma_<site>
//                             , (A0)(A1)(site)
//                             , ((ast_<A0, nt2::container::domain>))
//                               ((ast_<A1, nt2::container::domain>))
//                             )
//   {
//     typedef typename A0::value_type                   type_t;
//     typedef typename nt2::container::table<type_t>    t_t;
//     typedef  t_t                                      result_type;

//      BOOST_FORCEINLINE result_type operator()(A0& a, A1& b) const
//     {
//       nt2_la_int lda = a.leading_size();
//       nt2_la_int m = nt2::height(a);
//       nt2_la_int na = nt2::width(a);
//       nt2_la_int nhrs = nt2::width(b);
//       nt2_la_int ldb = nt2::height(b);
//       nt2_la_int nb = magma_get_dgeqrf_nb(m);
//       nt2_la_int lwkopt = (2*std::min(m,na)+ ((na+31)/32)*32)*nb;
//       nt2_la_int info;
//       double one = 1;
//       double negone = -1;

//       t_t x(nt2::of_size(ldb,nhrs));
//       nt2::container::table<float> tau(nt2::of_size(std::min(m,na),1));

//       details::magma_buffer<double>      dA(m,na,a.raw() );
//       details::magma_buffer<double>      dB(ldb,nhrs,b.raw() );
//       details::magma_buffer<double>      dX(ldb,nhrs);
//       details::magma_buffer<double>      dE(ldb,nhrs);
//       details::magma_buffer<double>      temp(ldb,nhrs);
//       details::magma_buffer<float>       dSR(m,na);
//       details::magma_buffer<float>       dSX(ldb,nhrs);
//       details::magma_buffer<float>       dT(lwkopt,nhrs);

//       double eps = boost::simd::Eps<double>();
//       double anrm = magmablas_dlange('I', m, na, dA.raw(), m, dE.raw() );
//       double cte = anrm*eps*nt2::sqrt( type_t(na));
//       double xnrm, rnrm;

//       magmablas_dlag2s(m,na,dA.raw(),m,dSR.raw(),m, &info);

//       magmablas_dlag2s(ldb,nhrs,dB.raw(),ldb,dSX.raw(),ldb,&info);

//       magmablas_sgemv( 't', m, na, one, dSR.raw(), m, dSX.raw(), one, 0, dSX.raw(), one );

//       magma_sgeqrf2_gpu( m, na, dSR.raw(), m, tau.raw(), &info );

//       magmablas_strsm('l','u','t','n',na,nhrs,(float)one,dSR.raw(),m,dSX.raw(), na);

//       magmablas_strsm('l','u','n','n',na,nhrs,(float)one,dSR.raw(),m,dSX.raw(), na);

//       magmablas_slag2d(ldb,nhrs,dSX.raw(),ldb,dX.raw(),ldb,&info);

//       magmablas_dlacpy('A', ldb, nhrs, dB.raw(), ldb, dE.raw(), ldb);

//       magmablas_dgemv( 'n', lda, na, negone, dA.raw(), lda, dX.raw(), one, one, dE.raw(), one );

//       for(size_t i = 1; i<=10;++i)
//       {
//         magmablas_dgemv( 't', lda, na, one, dA.raw(), lda, dE.raw(), one, 0, temp.raw(), one );
//         magmablas_dlag2s(ldb,nhrs,temp.raw(),ldb,dSX.raw(),ldb,&info);

//         magmablas_strsm('l','u','t','n',na,nhrs,(float)one,dSR.raw(),m,dSX.raw(), na);

//         magmablas_strsm('l','u','n','n',na,nhrs,(float)one,dSR.raw(),m,dSX.raw(), na);

//         magmablas_slag2d(na,nhrs,dSX.raw(),ldb,dE.raw(),ldb,&info);

//         dE.raw(x.raw());
//         rnrm = nt2::maximum(nt2::abs(x(_)));

//         magmablas_dgeadd(na,nhrs,one,dE.raw(),ldb,dX.raw(),ldb);

//         dX.raw(x.raw());
//         xnrm = nt2::maximum(nt2::abs(x(_)));

//         magmablas_dlacpy('A', ldb, nhrs, dB.raw(), ldb, dE.raw(), ldb);
//         magmablas_dgemv( 'n', lda, na, negone, dA.raw(), lda, dX.raw(), one, one, dE.raw(), one );

//         if(rnrm < xnrm*cte) { break; }
//       }

//        dX.raw(x.raw());

//        return x(_(1,na));
//     }
//   };

// } }

// #endif

// #endif


  namespace nt2{ namespace ext
  {
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mcsne_, nt2::tag::magma_<site>
                              , (A0)(A1)(site)
                              , ((ast_<A0, nt2::container::domain>))
                                ((ast_<A1, nt2::container::domain>))
                              )
    {
      typedef typename A0::value_type type_t;
      typedef typename nt2::container::table<type_t> t_t;
      typedef  t_t                                      result_type;

       BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const& b) const
      {
        nt2_la_int lda = a.leading_size();
        nt2_la_int na = nt2::width(a);
        nt2_la_int n = nt2::width(b);
        nt2_la_int ldb = b.leading_size();
        nt2_la_int  ldda = ((lda+31)/32)*32;

        t_t e,x;

        double eps = boost::simd::Eps<double>();
        double anrm = nt2::lange( boost::proto::value(a),'I');
        double cte = anrm*eps*nt2::sqrt( type_t(na));
        double xnrm, rnrm;

        nt2::table<float> sa,sb,sx,sr,sr1(nt2::of_size(na,na));
        sa = nt2::cast<float>(a);

        sr = nt2::qr(sa,nt2::no_pivot_);

        size_t size_n = sizeof(float)*(na);

        for(size_t i= 0; i < na; i++ )
        {
          std::memcpy(sr1.raw()+i*na ,sr.raw()+i*lda , size_n );
        }

       boost::proto::value(sr).swap(boost::proto::value(sr1) );

        sx= nt2::mtimes(nt2::trans(sa),nt2::cast<float>(b));

        nt2::trsm('l','u','t','n',boost::proto::value(sr),boost::proto::value(sx));
        nt2::trsm('l','u','n','n',boost::proto::value(sr),boost::proto::value(sx));

        x = nt2::cast<double>(sx);
        e = b - nt2::mtimes(a,x);

        for(size_t i = 1; i<=10;++i)
        {
          sx = nt2::cast<float> (nt2::mtimes(nt2::trans(a),e) ) ;

          nt2::trsm('l','u','t','n',boost::proto::value(sr),boost::proto::value(sx));
          nt2::trsm('l','u','n','n',boost::proto::value(sr),boost::proto::value(sx));

          e = nt2::cast<double>(sx);
          rnrm = nt2::maximum(nt2::abs(e(_)));
          x = x + e;
          e = b - nt2::mtimes(a,x);

          xnrm = nt2::maximum(nt2::abs(x(_)));

          if(rnrm < xnrm*cte) { return x; }
        }
        return x;
      }
   };

  } }

 #endif

  #endif

