/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_PACK_HPP
#define SPROUT_UTILITY_PACK_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type/type_tuple.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	//
	// pack_element
	//
	template<std::size_t I, typename... Args>
	struct pack_element
		: public std::tuple_element<I, sprout::types::type_tuple<Args...> >
	{};

	//
	// pack_element_c
	//
	template<std::size_t I, typename T, T... Args>
	struct pack_element_c
		: public sprout::pack_element<I, sprout::integral_constant<T, Args>...>
	{};

	//
	// pack_get
	//
	namespace detail {
		template<typename Tup>
		struct pack_get_helper;
		template<typename... Args>
		struct pack_get_helper<sprout::types::type_tuple<Args...> > {
			template<typename Head, typename... Tail>
			static SPROUT_CONSTEXPR Head&&
			eval(Args&&..., Head&& head, Tail&&...) {
				return SPROUT_FORWARD(Head, head);
			}
		};
	}	// namespace detail
	template<std::size_t I, typename... Args>
	inline SPROUT_CONSTEXPR typename sprout::pack_element<I, Args&&...>::type
	pack_get(Args&&... args) {
		return sprout::detail::pack_get_helper<
			typename sprout::types::detail::tuple_take<I, sprout::types::type_tuple<Args...> >::type
		>::eval(SPROUT_FORWARD(Args, args)...);
	}

	//
	// head_element
	//
	template<typename... Args>
	struct head_element;
	template<typename Head, typename... Tail>
	struct head_element<Head, Tail...>
		: public sprout::identity<Head>
	{};
	template<>
	struct head_element<>
		: public sprout::detail::nil_base
	{};

	//
	// head_get
	//
	template<typename Head, typename... Tail>
	inline SPROUT_CONSTEXPR Head&&
	head_get(Head&& head, Tail&&...) {
		return SPROUT_FORWARD(Head, head);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PACK_HPP
