/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_PAIR_PAIR_HPP
#define SPROUT_UTILITY_PAIR_PAIR_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/pair_decl.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	//
	// pair
	//
	template<typename T1, typename T2>
	template<typename... Args1, typename... Args2, sprout::index_t... Indexes1, sprout::index_t... Indexes2>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(
		sprout::tuples::tuple<Args1...> first_args, sprout::tuples::tuple<Args2...> second_args,
		sprout::index_tuple<Indexes1...>, sprout::index_tuple<Indexes2...>
		)
		: first(sprout::tuples::get<Indexes1>(first_args)...)
		, second(sprout::tuples::get<Indexes2>(second_args)...)
	{}
#if SPROUT_USE_DELEGATING_CONSTRUCTORS
	template<typename T1, typename T2>
	template<
		typename... Args1, typename... Args2,
		typename
	>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(
		std::piecewise_construct_t,
		sprout::tuples::tuple<Args1...> first_args, sprout::tuples::tuple<Args2...> second_args
		)
		: pair(
			first_args,
			second_args,
			sprout::index_pack<Args1...>::make(),
			sprout::index_pack<Args2...>::make()
			)
	{}
#endif	// #if SPROUT_USE_DELEGATING_CONSTRUCTORS
	template<typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(sprout::tuples::tuple<U, V> const& other)
		: first(sprout::tuples::get<0>(other))
		, second(sprout::tuples::get<1>(other))
	{}
	template<typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(sprout::tuples::tuple<U, V>&& other)
		: first(sprout::forward<U>(sprout::tuples::get<0>(other)))
		, second(sprout::forward<V>(sprout::tuples::get<1>(other)))
	{}

	template<typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline SPROUT_CXX14_CONSTEXPR sprout::pair<T1, T2>& sprout::pair<T1, T2>::operator=(sprout::tuples::tuple<U, V> const& rhs) {
		first = sprout::tuples::get<0>(rhs);
		second = sprout::tuples::get<0>(rhs);
		return *this;
	}
	template<typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline SPROUT_CXX14_CONSTEXPR sprout::pair<T1, T2>& sprout::pair<T1, T2>::operator=(sprout::tuples::tuple<U, V>&& rhs) {
		first = sprout::forward<U>(sprout::tuples::get<0>(rhs));
		second = sprout::forward<V>(sprout::tuples::get<1>(rhs));
		return *this;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_PAIR_HPP
