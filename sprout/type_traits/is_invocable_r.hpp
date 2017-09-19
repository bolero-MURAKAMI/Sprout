/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_INVOCABLE_R_HPP
#define SPROUT_TYPE_TRAITS_IS_INVOCABLE_R_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/invoke_result.hpp>
#include <sprout/type_traits/voider.hpp>

namespace sprout {
	//
	// is_invocable_r
	//
	namespace detail {
		template<typename R, typename Result, typename = void>
		struct is_invocable_r_impl
			: public sprout::false_type
		{};
		template<typename R, typename Result>
		struct is_invocable_r_impl<R, Result, typename sprout::voider<typename Result::type>::type>
			: public sprout::bool_constant<
				std::is_void<R>::value || std::is_convertible<typename Result::type, R>::value
			>
		{};
	}	// namespace detail
	template<typename R, typename F, typename... Args>
	struct is_invocable_r
		: public sprout::detail::is_invocable_r_impl<
			R, sprout::invoke_result<F, Args...>
		>::type
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename R, typename F, typename... Args>
	SPROUT_STATIC_CONSTEXPR bool is_invocable_r_v = sprout::is_invocable_r<R, F, Args...>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_INVOCABLE_R_HPP
