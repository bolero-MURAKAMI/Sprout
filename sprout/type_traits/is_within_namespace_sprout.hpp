/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_WITHIN_NAMESPACE_SPROUT_HPP
#define SPROUT_TYPE_TRAITS_IS_WITHIN_NAMESPACE_SPROUT_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/is_within_tag_namespace.hpp>

namespace sprout {
	SPROUT_ADL_TESTER_DECL(sprout);
}	// namespace sprout

namespace sprout {
	//
	// is_within_namespace_sprout
	//
	SPROUT_IS_WITHIN_NAMESPACE_DECL(sprout, sprout);
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_WITHIN_NAMESPACE_SPROUT_HPP
