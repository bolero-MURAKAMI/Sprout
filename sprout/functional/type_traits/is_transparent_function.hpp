/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_IS_TRANSPARENT_FUNCTION_HPP
#define SPROUT_FUNCTIONAL_TYPE_TRAITS_IS_TRANSPARENT_FUNCTION_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/has_xxx.hpp>

namespace sprout {
	//
	// is_transparent_function
	//
	SPROUT_HAS_XXX_TYPE_DEF(is_transparent_function, is_transparent);

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_transparent_function_v = sprout::is_transparent_function<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_IS_TRANSPARENT_FUNCTION_HPP
