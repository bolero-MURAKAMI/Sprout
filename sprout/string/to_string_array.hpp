#ifndef SPROUT_STRING_TO_STRING_ARRAY_HPP
#define SPROUT_STRING_TO_STRING_ARRAY_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/array/make_array.hpp>
#include <sprout/string/to_string_value.hpp>

namespace sprout {
	//
	// to_string_array
	//
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<T, sizeof...(Types)>
	to_string_array(Types&&... args) {
		return sprout::convert_array<T>(sprout::to_string_value(), sprout::forward<Types>(args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_TO_STRING_ARRAY_HPP
