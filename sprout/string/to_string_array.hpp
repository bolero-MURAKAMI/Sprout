/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_TO_STRING_ARRAY_HPP
#define SPROUT_STRING_TO_STRING_ARRAY_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/array/make_array.hpp>
#include <sprout/string/to_string_value.hpp>

namespace sprout {
	//
	// to_string_array
	//	[[deprecated]]
	//
	template<typename T, typename... Types>
	SPROUT_DEPRECATED
	inline SPROUT_CONSTEXPR sprout::array<T, sizeof...(Types)>
	to_string_array(Types&&... args) {
		return sprout::convert_array<T>(sprout::to_string_value(), SPROUT_FORWARD(Types, args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_TO_STRING_ARRAY_HPP
