/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_INVOCABLE_HPP
#define SPROUT_TYPE_TRAITS_IS_INVOCABLE_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/invoke_result.hpp>
#include <sprout/type_traits/voider.hpp>

namespace sprout {
	//
	// is_invocable
	//
	namespace detail {
		template<typename Result, typename = void>
		struct is_invocable_impl
			: public sprout::false_type
		{};
		template<typename Result>
		struct is_invocable_impl<Result, typename sprout::voider<typename Result::type>::type>
			: public sprout::true_type
		{};
	}	// namespace detail
	template<typename F, typename... Args>
	struct is_invocable
		: public sprout::detail::is_invocable_impl<
			sprout::invoke_result<F, Args...>
		>::type
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename F, typename... Args>
	SPROUT_STATIC_CONSTEXPR bool is_invocable_v = sprout::is_invocable<F, Args...>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_INVOCABLE_HPP
