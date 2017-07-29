/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_MAKE_VALARRAY_HPP
#define SPROUT_VALARRAY_MAKE_VALARRAY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/valarray/valarray.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/common_decay.hpp>

namespace sprout {
	namespace detail {
		enum make_valarray_t {
			make_valarray_in_common_elements
		};
	}	// namespace detail
	//
	// make_valarray
	//
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR sprout::valarray<typename std::remove_cv<T>::type, sizeof...(Types)>
	make_valarray(Types&&... args) {
		typedef sprout::valarray<typename std::remove_cv<T>::type, sizeof...(Types)> type;
		typedef sprout::detail::make_construct_impl<type> construct_type;
		return construct_type::make(T(SPROUT_FORWARD(Types, args))...);
	}
	template<typename T, std::size_t N, typename... Types>
	inline SPROUT_CONSTEXPR sprout::valarray<typename std::remove_cv<T>::type, N>
	make_valarray(Types&&... args) {
		typedef sprout::valarray<typename std::remove_cv<T>::type, N> type;
		typedef sprout::detail::make_construct_impl<type> construct_type;
		return construct_type::make(T(SPROUT_FORWARD(Types, args))...);
	}
	template<sprout::detail::make_valarray_t = sprout::detail::make_valarray_in_common_elements, typename... Types>
	inline SPROUT_CONSTEXPR sprout::valarray<typename sprout::common_decay<Types...>::type, sizeof...(Types)>
	make_valarray(Types&&... args) {
		typedef typename sprout::common_decay<Types...>::type value_type;
		typedef sprout::valarray<value_type, sizeof...(Types)> type;
		typedef sprout::detail::make_construct_impl<type> construct_type;
		return construct_type::make(value_type(SPROUT_FORWARD(Types, args))...);
	}
	template<std::size_t N, sprout::detail::make_valarray_t = sprout::detail::make_valarray_in_common_elements, typename... Types>
	inline SPROUT_CONSTEXPR sprout::valarray<typename sprout::common_decay<Types...>::type, N>
	make_valarray(Types&&... args) {
		typedef typename sprout::common_decay<Types...>::type value_type;
		typedef sprout::valarray<value_type, N> type;
		typedef sprout::detail::make_construct_impl<type> construct_type;
		return construct_type::make(value_type(SPROUT_FORWARD(Types, args))...);
	}

	//
	// make_valarray_without_narrowing
	//
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR sprout::valarray<typename std::remove_cv<T>::type, sizeof...(Types)>
	make_valarray_without_narrowing(Types&&... args) {
		typedef sprout::valarray<typename std::remove_cv<T>::type, sizeof...(Types)> type;
		typedef sprout::detail::make_construct_impl<type> construct_type;
		return construct_type::make(SPROUT_FORWARD(Types, args)...);
	}
	template<typename T, std::size_t N, typename... Types>
	inline SPROUT_CONSTEXPR sprout::valarray<typename std::remove_cv<T>::type, N>
	make_valarray_without_narrowing(Types&&... args) {
		typedef sprout::valarray<typename std::remove_cv<T>::type, N> type;
		typedef sprout::detail::make_construct_impl<type> construct_type;
		return construct_type::make(SPROUT_FORWARD(Types, args)...);
	}
	template<sprout::detail::make_valarray_t = sprout::detail::make_valarray_in_common_elements, typename... Types>
	inline SPROUT_CONSTEXPR sprout::valarray<typename sprout::common_decay<Types...>::type, sizeof...(Types)>
	make_valarray_without_narrowing(Types&&... args) {
		typedef typename sprout::common_decay<Types...>::type value_type;
		typedef sprout::valarray<value_type, sizeof...(Types)> type;
		typedef sprout::detail::make_construct_impl<type> construct_type;
		return construct_type::make(SPROUT_FORWARD(Types, args)...);
	}
	template<std::size_t N, sprout::detail::make_valarray_t = sprout::detail::make_valarray_in_common_elements, typename... Types>
	inline SPROUT_CONSTEXPR sprout::valarray<typename sprout::common_decay<Types...>::type, N>
	make_valarray_without_narrowing(Types&&... args) {
		typedef typename sprout::common_decay<Types...>::type value_type;
		typedef sprout::valarray<value_type, N> type;
		typedef sprout::detail::make_construct_impl<type> construct_type;
		return construct_type::make(SPROUT_FORWARD(Types, args)...);
	}

	//
	// make_common_valarray
	//
	template<typename... Types>
	inline SPROUT_CONSTEXPR sprout::valarray<typename sprout::common_decay<Types...>::type, sizeof...(Types)>
	make_common_valarray(Types&&... args) {
		return sprout::make_valarray(SPROUT_FORWARD(Types, args)...);
	}
	template<std::size_t N, typename... Types>
	inline SPROUT_CONSTEXPR sprout::valarray<typename sprout::common_decay<Types...>::type, N>
	make_common_valarray(Types&&... args) {
		return sprout::make_valarray<N>(SPROUT_FORWARD(Types, args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_MAKE_VALARRAY_HPP
