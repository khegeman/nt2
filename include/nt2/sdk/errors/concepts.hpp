/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_ERRORS_CONCEPTS_HPP_INCLUDED
#define NT2_SDK_ERRORS_CONCEPTS_HPP_INCLUDED

#include <boost/concept_check.hpp>

////////////////////////////////////////////////////////////////////////////////
// Concept checking macro definitions
// Documentation: http://nt2.lri.fr/sdk/errors/concepts.html
////////////////////////////////////////////////////////////////////////////////

#if defined(NT2_USE_CONCEPTS)
//////////////////////////////////////////////////////////////////////////////
// Mapping over BOOST_CONCEPT_ASSERT
//////////////////////////////////////////////////////////////////////////////
#define NT2_CONCEPT_ASSERT(CONCEPT) BOOST_CONCEPT_ASSERT(CONCEPT)

//////////////////////////////////////////////////////////////////////////////
// Mapping over BOOST_CONCEPT_REQUIRE
//////////////////////////////////////////////////////////////////////////////
#define NT2_CONCEPT_REQUIRE(CONCEPTS,TYPE)  BOOST_CONCEPT_REQUIRE(CONCEPT,TYPE)

#elif !defined(NT2_USE_CONCEPTS)
#define NT2_CONCEPT_ASSERT(CONCEPT)
#define NT2_CONCEPT_REQUIRE(CONCEPTS,TYPE)
#endif

#endif
