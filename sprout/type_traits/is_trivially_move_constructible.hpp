/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_HPP
#define SPROUT_TYPE_TRAITS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/is_trivially_constructible.hpp>

namespace sprout {
	//
	// is_trivially_move_constructible
	//
	namespace detail {
		template<typename T, bool = std::is_void<T>::value>
		struct is_trivially_move_constructible_impl
			: public sprout::false_type
		{};
		template<typename T>
		struct is_trivially_move_constructible_impl<T, false>
			: public sprout::is_trivially_constructible<T, T&&>
		{};
	}	// namespace detail
	template<typename T>
	struct is_trivially_move_constructible
		: public sprout::detail::is_trivially_move_constructible_impl<T>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_move_constructible_v = sprout::is_trivially_move_constructible<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_HPP
