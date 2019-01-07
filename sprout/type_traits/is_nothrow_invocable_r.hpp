/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_R_HPP
#define SPROUT_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_R_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/invoke_result.hpp>
#include <sprout/type_traits/voider.hpp>
#include <sprout/type_traits/detail/invoke.hpp>

namespace sprout {
	//
	// is_nothrow_invocable_r
	//
	namespace detail {
		template<bool Cond, typename R, typename F, typename... Args>
		struct is_nothrow_invocable_r_impl
			: public sprout::false_type
		{};
		template<typename R, typename F, typename... Args>
		struct is_nothrow_invocable_r_impl<true, R, F, Args...>
			: public sprout::bool_constant<
				SPROUT_NOEXCEPT_EXPR(sprout::detail::invoke<R>(std::declval<F>(), std::declval<Args>()...))
			>
		{};
	}	// namespace detail
	template<typename R, typename F, typename... Args>
	struct is_nothrow_invocable_r
		: public sprout::detail::is_nothrow_invocable_r_impl<
			sprout::is_invocable_r<R, F, Args...>::value, R, F, Args...
		>::type
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename R, typename F, typename... Args>
	SPROUT_STATIC_CONSTEXPR bool is_nothrow_invocable_r_v = sprout::is_nothrow_invocable_r<R, F, Args...>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_R_HPP
