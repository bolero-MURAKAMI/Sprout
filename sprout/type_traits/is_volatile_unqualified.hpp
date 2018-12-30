/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_VOLATILE_UNQUALIFIED_HPP
#define SPROUT_TYPE_TRAITS_IS_VOLATILE_UNQUALIFIED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_volatile_unqualified
	//
	template<typename T>
	struct is_volatile_unqualified
		: public sprout::bool_constant<
			std::is_volatile<T>::value
		>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_volatile_unqualified_v = sprout::is_volatile_unqualified<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_VOLATILE_UNQUALIFIED_HPP
