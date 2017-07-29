/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_WITHIN_NAMESPACE_BOOST_HPP
#define SPROUT_TYPE_TRAITS_IS_WITHIN_NAMESPACE_BOOST_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/is_within_tag_namespace.hpp>

namespace boost {
	SPROUT_ADL_TESTER_DECL(boost);
}	// namespace boost

namespace sprout {
	//
	// is_within_namespace_boost
	//
	SPROUT_IS_WITHIN_NAMESPACE_DECL(boost, boost);
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_WITHIN_NAMESPACE_BOOST_HPP
