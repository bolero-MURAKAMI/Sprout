/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_SWAPPABLE_HPP
#define SPROUT_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/is_swappable_with.hpp>

namespace sprout {
	//
	// is_swappable
	//
	template<typename T>
	struct is_swappable
		: public sprout::is_swappable_with<T&, T&>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_swappable_v = sprout::is_swappable<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_SWAPPABLE_HPP
