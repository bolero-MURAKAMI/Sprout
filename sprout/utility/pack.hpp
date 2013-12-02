/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_PACK_HPP
#define SPROUT_UTILITY_PACK_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type/type_tuple.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/enabler_if.hpp>

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
		: public sprout::pack_element<I, sprout::integral_constant<T, Args>...>::type
	{};

	//
	// pack_get
	//
	namespace detail {
		template<typename Tup>
		struct pack_get_helper;
		template<typename... Args>
		struct pack_get_helper<sprout::types::type_tuple<Args...> > {
			template<typename T>
			static SPROUT_CONSTEXPR T&&
			eval(Args&&..., T&& t, ...) {
				return sprout::forward<T>(t);
			}
		};
	}	// namespace detail
	template<std::size_t I, typename... Args>
	inline SPROUT_CONSTEXPR typename sprout::pack_element<I, Args&&...>::type
	pack_get(Args&&... args) {
		return sprout::detail::pack_get_helper<
			typename sprout::types::detail::tuple_take<I, sprout::types::type_tuple<Args...> >::type
		>::eval(sprout::forward<Args>(args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PACK_HPP
