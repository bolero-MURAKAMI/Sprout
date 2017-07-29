/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_UNSIGNED_HPP
#define SPROUT_TYPE_TRAITS_IS_UNSIGNED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	//
	// is_unsigned
	//
	namespace detail {
		template<typename T, bool = std::is_arithmetic<T>::value>
		struct is_unsigned_impl
			: public sprout::false_type
		{};
		template<typename T>
		struct is_unsigned_impl<T, true>
			: public sprout::detail::type_traits_wrapper<std::is_unsigned<T> >
		{};
	}	// namespace detail
	template<typename T>
	struct is_unsigned
		: public sprout::detail::is_unsigned_impl<T>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_unsigned_v = sprout::is_unsigned<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_UNSIGNED_HPP
