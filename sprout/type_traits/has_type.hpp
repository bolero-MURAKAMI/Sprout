/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_HAS_TYPE_HPP
#define SPROUT_TYPE_TRAITS_HAS_TYPE_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/has_xxx.hpp>

namespace sprout {
	//
	// has_type
	//
	SPROUT_HAS_XXX_TYPE_DEF_LAZY(type);

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool has_type_v = sprout::has_type<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_HAS_TYPE_HPP
