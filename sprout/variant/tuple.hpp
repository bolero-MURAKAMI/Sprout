/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VARIANT_TUPLE_HPP
#define SPROUT_VARIANT_TUPLE_HPP

#include <tuple>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/variant/variant.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	//
	// tuple_get
	//
	template<std::size_t I, typename... Types>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<
		I,
		sprout::variant<Types...>
	>::type const&
	tuple_get(sprout::variant<Types...> const& t) {
		return t.template get_at<I>();
	}
	template<std::size_t I, typename... Types>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<
		I,
		sprout::variant<Types...>
	>::type&
	tuple_get(sprout::variant<Types...>& t) {
		return t.template get_at<I>();
	}
	template<std::size_t I, typename... Types>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<
		I,
		sprout::variant<Types...>
	>::type&&
	tuple_get(sprout::variant<Types...>&& t) {
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<typename... Types>
	struct tuple_size<sprout::variant<Types...> >
		: public std::tuple_size<typename sprout::variant<Types...>::tuple_type>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename... Types>
	struct tuple_element<I, sprout::variant<Types...> >
		: public std::tuple_element<I, typename sprout::variant<Types...>::tuple_type>
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_VARIANT_TUPLE_HPP
