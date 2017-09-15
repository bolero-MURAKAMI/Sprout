/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_RESULT_OF_HPP
#define SPROUT_TYPE_TRAITS_RESULT_OF_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace detail {
		template<typename F, typename... Args>
		inline SPROUT_CONSTEXPR decltype(std::declval<F>()(std::declval<Args>()...))
		invoke(F&&, Args&&...);

		template<typename Base, typename T, typename Derived>
		inline SPROUT_CONSTEXPR decltype(std::declval<Derived>().*(std::declval<T Base::*>()))
		invoke(T Base::*, Derived&&);

		template<typename PMD, typename Pointer>
		inline SPROUT_CONSTEXPR decltype((*std::declval<Pointer>()).*(std::declval<PMD>()))
		invoke(PMD&&, Pointer&&);

		template<typename Base, typename T, typename Derived, typename... Args>
		inline SPROUT_CONSTEXPR decltype((std::declval<Derived>().*(std::declval<T Base::*>()))(std::declval<Args>()...))
		invoke(T Base::*, Derived&&, Args&&...);

		template<typename PMF, typename Pointer, typename... Args>
		inline SPROUT_CONSTEXPR decltype(((*std::declval<Pointer>()).*(std::declval<PMF>()))(std::declval<Args>()...))
		invoke(PMF&& pmf, Pointer&& ptr, Args&&... args);
	}	// namespace detail

	namespace detail {
		template<typename Void, typename, typename...>
		struct invoke_result {};
		template<typename F, typename...Args>
		struct invoke_result<decltype(void(sprout::detail::invoke(std::declval<F>(), std::declval<Args>()...))), F, Args...>
			: public sprout::identity<decltype(sprout::detail::invoke(std::declval<F>(), std::declval<Args>()...))>
		{};
	}	// namespace detail

	//
	// result_of
	//
	template<typename>
	struct result_of;
	template<typename F, typename... Args>
	struct result_of<F(Args...)>
		: public sprout::detail::invoke_result<void, F, Args...>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using result_of_t = typename sprout::result_of<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_RESULT_OF_HPP
