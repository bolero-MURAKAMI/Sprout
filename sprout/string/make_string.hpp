/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
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
	//
	// make_string
	//
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR sprout::basic_string<typename std::decay<T>::type, 1 + sizeof...(Types)>
	make_string(T&& t, Types&&... args) {
		typedef sprout::detail::make_construct_impl<
			sprout::basic_string<typename std::decay<T>::type, 1 + sizeof...(Types)>
		> impl_type;
		return impl_type::make(SPROUT_FORWARD(T, t), SPROUT_FORWARD(Types, args)...);
	}

	//
	// make_string_as
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string<typename std::decay<T>::type, 0>
	make_string_as() {
		return sprout::basic_string<typename std::decay<T>::type, 0>();
	}
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR sprout::basic_string<typename std::decay<T>::type, sizeof...(Types)>
	make_string_as(Types&&... args) {
		typedef sprout::detail::make_construct_impl<
			sprout::basic_string<typename std::decay<T>::type, sizeof...(Types)>
		> impl_type;
		return impl_type::make(SPROUT_FORWARD(Types, args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_MAKE_STRING_HPP
