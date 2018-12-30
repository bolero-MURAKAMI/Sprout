/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP
#define SPROUT_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/invoke_result.hpp>
#include <sprout/type_traits/is_invocable.hpp>
#include <sprout/type_traits/detail/invoke.hpp>

namespace sprout {
	//
	// is_nothrow_invocable
	//
	namespace detail {
		template<bool Cond, typename F, typename... Args>
		struct is_nothrow_invocable_impl
			: public sprout::false_type
		{};
		template<typename F, typename... Args>
		struct is_nothrow_invocable_impl<true, F, Args...>
			: public sprout::bool_constant<
				SPROUT_NOEXCEPT_EXPR(sprout::detail::invoke(std::declval<F>(), std::declval<Args>()...))
			>
		{};
	}	// namespace detail
	template<typename F, typename... Args>
	struct is_nothrow_invocable
		: public sprout::detail::is_nothrow_invocable_impl<
			sprout::is_invocable<F, Args...>::value, F, Args...
		>::type
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename F, typename... Args>
	SPROUT_STATIC_CONSTEXPR bool is_nothrow_invocable_v = sprout::is_nothrow_invocable<F, Args...>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP
