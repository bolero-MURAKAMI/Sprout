/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ARRAY_MAKE_ARRAY_HPP
#define SPROUT_ARRAY_MAKE_ARRAY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/array/array.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/common_decay.hpp>

namespace sprout {
	namespace detail {
		enum make_array_t {
			make_array_in_common_elements
		};
	}	// namespace detail
	//
	// make_array
	//
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<typename std::remove_cv<T>::type, sizeof...(Types)>
	make_array(Types&&... args) {
		return sprout::array<typename std::remove_cv<T>::type, sizeof...(Types)>{{T(SPROUT_FORWARD(Types, args))...}};
	}
	template<typename T, std::size_t N, typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<typename std::remove_cv<T>::type, N>
	make_array(Types&&... args) {
		return sprout::array<typename std::remove_cv<T>::type, N>{{T(SPROUT_FORWARD(Types, args))...}};
	}
	template<sprout::detail::make_array_t = sprout::detail::make_array_in_common_elements, typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<typename sprout::common_decay<Types...>::type, sizeof...(Types)>
	make_array(Types&&... args) {
		typedef typename sprout::common_decay<Types...>::type value_type;
		typedef sprout::array<value_type, sizeof...(Types)> type;
		return type{{value_type(SPROUT_FORWARD(Types, args))...}};
	}
	template<std::size_t N, sprout::detail::make_array_t = sprout::detail::make_array_in_common_elements, typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<typename sprout::common_decay<Types...>::type, N>
	make_array(Types&&... args) {
		typedef typename sprout::common_decay<Types...>::type value_type;
		typedef sprout::array<value_type, N> type;
		return type{{value_type(SPROUT_FORWARD(Types, args))...}};
	}

	//
	// make_array_without_narrowing
	//
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<typename std::remove_cv<T>::type, sizeof...(Types)>
	make_array_without_narrowing(Types&&... args) {
		return sprout::array<typename std::remove_cv<T>::type, sizeof...(Types)>{{SPROUT_FORWARD(Types, args)...}};
	}
	template<typename T, std::size_t N, typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<typename std::remove_cv<T>::type, N>
	make_array_without_narrowing(Types&&... args) {
		return sprout::array<typename std::remove_cv<T>::type, N>{{SPROUT_FORWARD(Types, args)...}};
	}
	template<sprout::detail::make_array_t = sprout::detail::make_array_in_common_elements, typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<typename sprout::common_decay<Types...>::type, sizeof...(Types)>
	make_array_without_narrowing(Types&&... args) {
		typedef typename sprout::common_decay<Types...>::type value_type;
		typedef sprout::array<value_type, sizeof...(Types)> type;
		return type{{SPROUT_FORWARD(Types, args)...}};
	}
	template<std::size_t N, sprout::detail::make_array_t = sprout::detail::make_array_in_common_elements, typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<typename sprout::common_decay<Types...>::type, N>
	make_array_without_narrowing(Types&&... args) {
		typedef typename sprout::common_decay<Types...>::type value_type;
		typedef sprout::array<value_type, N> type;
		return type{{SPROUT_FORWARD(Types, args)...}};
	}

	//
	// make_common_array
	//
	template<typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<typename sprout::common_decay<Types...>::type, sizeof...(Types)>
	make_common_array(Types&&... args) {
		return sprout::make_array(SPROUT_FORWARD(Types, args)...);
	}
	template<std::size_t N, typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<typename sprout::common_decay<Types...>::type, N>
	make_common_array(Types&&... args) {
		return sprout::make_array<N>(SPROUT_FORWARD(Types, args)...);
	}

	//
	// convert_array
	//	[[deprecated]]
	//
	template<typename T, typename Converter, typename... Types>
	SPROUT_DEPRECATED
	inline SPROUT_CONSTEXPR sprout::array<T, sizeof...(Types)>
	convert_array(Converter&& conv, Types&&... args) {
		return sprout::make_array<T>(SPROUT_FORWARD(Converter, conv)(SPROUT_FORWARD(Types, args))...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ARRAY_MAKE_ARRAY_HPP
