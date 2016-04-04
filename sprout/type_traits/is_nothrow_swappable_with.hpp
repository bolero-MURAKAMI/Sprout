/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
#define SPROUT_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/is_swappable_with.hpp>

namespace sprout_nothrow_swappable_detail {
	using std::swap;

	template<typename T, typename U>
	struct is_nothrow_swappable_with
		: public sprout::bool_constant<
			SPROUT_NOEXCEPT_EXPR(swap(std::declval<T>(), std::declval<U>()))
				&& SPROUT_NOEXCEPT_EXPR(swap(std::declval<U>(), std::declval<T>()))
		>::type
	{};
}	// namespace sprout_nothrow_swappable_detail

namespace sprout {
	namespace detail {
		template<typename T, typename U, bool = false>
		struct is_nothrow_swappable_with_impl
			: public sprout::false_type
		{};
		template<typename T, typename U>
		struct is_nothrow_swappable_with_impl<T, U, true>
			: public sprout_nothrow_swappable_detail::is_nothrow_swappable_with<T, U>
		{};
	}	// namespace detail
	//
	// is_nothrow_swappable_with
	//
	template<typename T, typename U>
	struct is_nothrow_swappable_with
		: public sprout::detail::is_nothrow_swappable_with_impl<T, U, sprout::is_swappable_with<T, U>::value>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T, typename U>
	SPROUT_STATIC_CONSTEXPR bool is_nothrow_swappable_with_v = sprout::is_nothrow_swappable_with<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
