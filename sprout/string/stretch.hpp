#ifndef SPROUT_STRING_STRETCH_HPP
#define SPROUT_STRING_STRETCH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/string/string.hpp>

namespace sprout {
	//
	// stretch
	//
	template<std::size_t To, typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, To, Traits>
	stretch(sprout::basic_string<T, N, Traits> const& s) {
		return s;
	}

	template<std::size_t To, typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, To>
	stretch(T const(& arr)[N]) {
		return sprout::stretch<To>(sprout::to_string(arr));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_STRETCH_HPP
