//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MAGMA_GESVD_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MAGMA_GESVD_HPP_INCLUDED

#if defined(NT2_USE_MAGMA)

#include <nt2/linalg/functions/gesvd.hpp>
#include <nt2/include/functions/xerbla.hpp>
#include <nt2/sdk/magma/magma.hpp>
#include <nt2/core/container/table/kind.hpp>

#include <nt2/dsl/functions/terminal.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <magma.h>

namespace nt2 { namespace ext
{
   /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)(site)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >))
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))
                              ((container_<nt2::tag::table_,  double_<A2>, S2 >))
                              ((container_<nt2::tag::table_,  double_<A3>, S3 >))
                              (scalar_< ints8_<A4> >)
                              (scalar_< ints8_<A5> >)

                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a0, A1& s, A2& u,A3 &vt, A4 const jobu
                                             , A5 const jobvt) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;
        nt2_la_int lwork_query = -1;

        magma_dgesvd(jobu,jobvt,m, n, 0, ld, 0, 0, ldu
                            , 0, ldvt, w.main()
                            , lwork_query, &that
                            );

          w.prepare_main();
          nt2::gesvd(a0,s,u,vt,jobu,jobvt,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)(A6)(site)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >))
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))
                              ((container_<nt2::tag::table_,  double_<A2>, S2 >))
                              ((container_<nt2::tag::table_,  double_<A3>, S3 >))
                              (scalar_< ints8_<A4> >)
                              (scalar_< ints8_<A5> >)
                              (unspecified_<A6>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a0, A1& s,A2& u, A3& vt, A4 const jobu
                                             , A5 const jobvt, A6& w) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;
        nt2_la_int  wn = w.main_size();

        magma_dgesvd( jobu,jobvt,m, n, a0.raw(), ld, s.raw(), u.raw(), ldu
                            , vt.raw(), ldvt, w.main()
                            , wn, &that
                            );
        return that;
     }
  };


   /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)(site)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >))
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))
                              ((container_<nt2::tag::table_,  single_<A2>, S2 >))
                              ((container_<nt2::tag::table_,  single_<A3>, S3 >))
                              (scalar_< ints8_<A4> >)
                              (scalar_< ints8_<A5> >)

                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a0, A1& s, A2& u,A3 &vt, A4 const jobu
                                             , A5 const jobvt) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;
        nt2_la_int lwork_query = -1;

        magma_sgesvd(jobu,jobvt,m, n, 0, ld, 0, 0, ldu
                            , 0, ldvt, w.main()
                            , lwork_query, &that
                            );

          w.prepare_main();
          nt2::gesvd(a0,s,u,vt,jobu,jobvt,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)(A6)(site)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >))
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))
                              ((container_<nt2::tag::table_,  single_<A2>, S2 >))
                              ((container_<nt2::tag::table_,  single_<A3>, S3 >))
                              (scalar_< ints8_<A4> >)
                              (scalar_< ints8_<A5> >)
                              (unspecified_<A6>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a0, A1& s,A2& u, A3& vt, A4 const jobu
                                             , A5 const jobvt, A6& w) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;
        nt2_la_int  wn = w.main_size();

        magma_sgesvd( jobu,jobvt,m, n, a0.raw(), ld, s.raw(), u.raw(), ldu
                            , vt.raw(), ldvt, w.main()
                            , wn, &that
                            );
        return that;
     }
  };

//---------------------------------------------Complex------------------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)(site)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >))
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))
                              ((container_<nt2::tag::table_,  complex_<single_<A3> >, S3 >))
                              (scalar_< ints8_<A4> >)
                              (scalar_< ints8_<A5> >)

                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s, A2& u,A3 &vt, A4 const jobu, A5 const jobvt) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;
        nt2_la_int lwork_query = -1;

        magma_cgesvd( jobu,jobvt,m, n, 0, ld, 0, 0, ldu
                            , 0, ldvt, (cuFloatComplex*)w.main()
                            , lwork_query, 0, &that
                            );

          w.prepare_main();
          nt2::gesvd(a0,s,u,vt,jobu,jobvt,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)(A6)(site)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >))
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))
                              ((container_<nt2::tag::table_,  complex_<single_<A3> >, S3 >))
                              (scalar_< ints8_<A4> >)
                              (scalar_< ints8_<A5> >)
                              (unspecified_<A6>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s,A2& u, A3& vt, A4 const jobu, A5 const jobvt, A6& w) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;
        nt2_la_int  wn = w.main_size();

        nt2::container::table<float> rwork(nt2::of_size(5*std::min(m,n),1));

        magma_cgesvd( jobu,jobvt,m, n, (cuFloatComplex*)a0.raw(), ld, s.raw()
                            , (cuFloatComplex*)u.raw(), ldu
                            , (cuFloatComplex*)vt.raw(), ldvt, (cuFloatComplex*)w.main()
                            , wn, rwork.raw(), &that
                            );
        return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)(site)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >))
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))
                              ((container_<nt2::tag::table_,  complex_<double_<A3> >, S3 >))
                              (scalar_< ints8_<A4> >)
                              (scalar_< ints8_<A5> >)

                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s, A2& u,A3 &vt, A4 const jobu, A5 const jobvt) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;
        nt2_la_int lwork_query = -1;

        magma_zgesvd(jobu,jobvt,m, n, 0, ld, 0, 0, ldu
                            , 0, ldvt, (cuDoubleComplex*)w.main()
                            , lwork_query, 0, &that
                            );

          w.prepare_main();
          nt2::gesvd(a0,s,u,vt,jobu,jobvt,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, nt2::tag::magma_<site>
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)(A6)(site)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >))
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))
                              ((container_<nt2::tag::table_,  complex_<double_<A3> >, S3 >))
                              (scalar_< ints8_<A4> >)
                              (scalar_< ints8_<A5> >)
                              (unspecified_<A6>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s,A2& u, A3& vt, A4 const jobu, A5 const jobvt, A6& w) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;
        nt2_la_int  wn = w.main_size();

        nt2::container::table<double> rwork(nt2::of_size(5*std::min(m,n),1));

        magma_zgesvd( jobu,jobvt,m, n, (cuDoubleComplex*)a0.raw(), ld, s.raw()
                            , (cuDoubleComplex*)u.raw(), ldu
                            , (cuDoubleComplex*)vt.raw(), ldvt, (cuDoubleComplex*)w.main()
                            , wn, rwork.raw(), &that
                            );
        return that;
     }
  };
} }

#endif
#endif

