//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_SNE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_SNE_HPP_INCLUDED

#include <nt2/linalg/functions/sne.hpp>
#include <nt2/include/functions/lange.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/trsm.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/blas/blas2.hpp>
#include <nt2/linalg/details/blas/blas3.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/colon.hpp>

#include <nt2/core/container/table/table.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sne_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type type_t;
    typedef typename nt2::container::table<type_t> t_t;
    typedef  t_t                                      result_type;

     BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const& b) const
    {
      nt2_la_int na = nt2::width(a);
      t_t r = nt2::qr(a,nt2::no_pivot_);
      r= nt2::triu( r( _(1,na), _ ) );

      t_t x = nt2::mtimes(nt2::trans(a),b);

      nt2::trsm('l','u','t','n',boost::proto::value(r),boost::proto::value(x));

      nt2::trsm('l','u','n','n',boost::proto::value(r),boost::proto::value(x));

      return x;
    }
  };

} }

#endif

