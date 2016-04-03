/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_MAKE_STRING_HPP
#define SPROUT_STRING_MAKE_STRING_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/string/char_traits.hpp>
#include <sprout/string/string.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace detail {
		enum make_string_t {
			make_string_in_head_type
		};
	}	// namespace detail
	//
	// make_string
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string<typename std::decay<T>::type, 0>
	make_string() {
		return sprout::basic_string<typename std::decay<T>::type, 0>();
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::basic_string<typename std::decay<T>::type, N>
	make_string() {
		return sprout::basic_string<typename std::decay<T>::type, N>();
	}
	template<typename T, typename Head, typename... Tail>
	inline SPROUT_CONSTEXPR sprout::basic_string<typename std::decay<T>::type, 1 + sizeof...(Tail)>
	make_string(Head&& head, Tail&&... tail) {
		typedef sprout::detail::make_construct_impl<
			sprout::basic_string<typename std::decay<T>::type, 1 + sizeof...(Tail)>
		> impl_type;
		return impl_type::make(SPROUT_FORWARD(Head, head), SPROUT_FORWARD(Tail, tail)...);
	}
	template<typename T, std::size_t N, typename Head, typename... Tail>
	inline SPROUT_CONSTEXPR sprout::basic_string<typename std::decay<T>::type, N>
	make_string(Head&& head, Tail&&... tail) {
		typedef sprout::detail::make_construct_impl<
			sprout::basic_string<typename std::decay<T>::type, N>
		> impl_type;
		return impl_type::make(SPROUT_FORWARD(Head, head), SPROUT_FORWARD(Tail, tail)...);
	}
	template<sprout::detail::make_string_t = sprout::detail::make_string_in_head_type, typename Head, typename... Tail>
	inline SPROUT_CONSTEXPR sprout::basic_string<typename std::decay<Head>::type, 1 + sizeof...(Tail)>
	make_string(Head&& head, Tail&&... tail) {
		typedef sprout::detail::make_construct_impl<
			sprout::basic_string<typename std::decay<Head>::type, 1 + sizeof...(Tail)>
		> impl_type;
		return impl_type::make(SPROUT_FORWARD(Head, head), SPROUT_FORWARD(Tail, tail)...);
	}
	template<std::size_t N, sprout::detail::make_string_t = sprout::detail::make_string_in_head_type, typename Head, typename... Tail>
	inline SPROUT_CONSTEXPR sprout::basic_string<typename std::decay<Head>::type, N>
	make_string(Head&& head, Tail&&... tail) {
		typedef sprout::detail::make_construct_impl<
			sprout::basic_string<typename std::decay<Head>::type, N>
		> impl_type;
		return impl_type::make(SPROUT_FORWARD(Head, head), SPROUT_FORWARD(Tail, tail)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_MAKE_STRING_HPP
