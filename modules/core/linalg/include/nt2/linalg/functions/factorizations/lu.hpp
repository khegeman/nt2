//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_LU_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_LU_HPP_INCLUDED

#include <nt2/linalg/functions/lu.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/getrf.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tri1l.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/sdk/meta/concrete.hpp>
#include <nt2/sdk/error/warning.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - D = LU(A)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lu_, tag::cpu_
                            , (A0)(N0)(A1)
                            , ((node_ < A0, nt2::tag::lu_
                                      , N0, nt2::container::domain
                                      >
                              ))
                              ((node_ < A1, nt2::tag::tie_
                                      , boost::mpl::long_<1>
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,0>::type  c0_t;
      typedef typename meta::concrete<c0_t>::type                     c_t;

      c_t out = shallow_concrete( boost::proto::child_c<0>(a1)
                                , boost::proto::child_c<0>(a0)
                                );

      nt2::container::table<nt2_la_int> ip;
      nt2_la_int lapack_info = nt2::getrf(boost::proto::value(out),boost::proto::value(ip));
      boost::dispatch::ignore_unused(lapack_info);

      NT2_WARNING ( lapack_info <= 0
                  , "LU factorization has been completed, but U is exactly "
                    "singular. Division by zero will occur if it is used to "
                    "solve a system of equations."
                  );

      boost::proto::child_c<0>(a1) = out;
    }
  };

  /// INTERNAL ONLY - [L,U,P*] = LU(A)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lu_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_ < A0, nt2::tag::lu_
                                      , N0, nt2::container::domain
                                      >
                              ))
                              ((node_ < A1, nt2::tag::tie_
                                      , N1, nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef void                                              result_type;
    typedef typename boost::proto::result_of
                                 ::child_c<A1&,0>::value_type c0_t;
    typedef typename boost::dispatch::meta::
            terminal_of< typename boost::dispatch
                                       ::meta::semantic_of<c0_t>::type
                       >::type                                tab0_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      nt2::container::table<nt2_la_int> ip;
      decomp(a0, a1, ip, N1());
    }

    /// INTERNAL ONLY - [L,U] = LU(A)
    BOOST_FORCEINLINE
    void decomp ( A0& a0, A1& a1, nt2::container::table<nt2_la_int>& ip
                , boost::mpl::long_<2> const&
                ) const
    {
      nt2_la_int info;

      if( nt2::issquare(boost::proto::child_c<0>(a0)) )
      {
        typedef typename boost::proto::result_of::child_c<A1&,0>::type  s0_t;
        typedef typename meta::concrete<s0_t>::type                     c_t;

        c_t work = shallow_concrete ( boost::proto::child_c<0>(a1)
                                    , boost::proto::child_c<0>(a0)
                                    );

        info = nt2::getrf(boost::proto::value(work),boost::proto::value(ip));
        extract_lu(a1,work);
      }
      else
      {
        tab0_t work = boost::proto::child_c<0>(a0);
        info = nt2::getrf(boost::proto::value(work),boost::proto::value(ip));
        extract_lu(a1,work);
      }

      check_success(info);
    }

    /// INTERNAL ONLY - [L,U,P] = LU(A)
    BOOST_FORCEINLINE
    void decomp ( A0& a0, A1& a1, nt2::container::table<nt2_la_int>& ip
                , boost::mpl::long_<3> const&
                ) const
    {
      decomp(a0,a1,ip,boost::mpl::long_<2>());
      extract_p(a1,ip);
    }

    /// INTERNAL ONLY - Helper for L/U extraction
    template<typename W>
    BOOST_FORCEINLINE void extract_lu(A1& a1, W& work) const
    {
      std::size_t d  = dim(work);
      boost::proto::child_c<1>(a1) = nt2::triu( work( nt2::_(1, d), nt2::_) );
      boost::proto::child_c<0>(a1) = nt2::tri1l( work(nt2::_, nt2::_(1, d) ) );
    }

    /// INTERNAL ONLY - Size of L/U
    template<typename W>
    BOOST_FORCEINLINE std::size_t dim(W const& work) const
    {
      return std::min(nt2::height(work),nt2::width(work));
    }

    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void extract_p(A1& a1, nt2::container::table<nt2_la_int>& ip) const
    {
      typedef typename boost::proto::result_of
                                 ::child_c<A1&,2>::value_type::value_type t_t;

      std::size_t d = nt2::numel(ip);
      boost::proto::child_c<2>(a1) = nt2::zeros(d, meta::as_<t_t>());

      for(std::size_t i = 1; i<= d;++i)
        boost::proto::child_c<2>(a1)(i,ip(i)) = 1;
    }

    /// INTERNAL ONLY
    void check_success(nt2_la_int lapack_info) const
    {
      boost::dispatch::ignore_unused(lapack_info);
      NT2_WARNING ( lapack_info <= 0
                  , "LU factorization has been completed, but U is exactly "
                    "singular. Division by zero will occur if it is used to "
                    "solve a system of equations."
                  );
    }
  };
} }

#endif
