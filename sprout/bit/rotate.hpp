#ifndef SPROUT_BIT_ROTATE_HPP
#define SPROUT_BIT_ROTATE_HPP

#include <cstddef>
#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// left_rotate
	//
	template<typename T, typename sprout::enabler_if<std::is_integral<T>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR T
	left_rotate(T x, std::size_t n) {
		return (x << n) ^ (x >> (sizeof(T) * CHAR_BIT - n));
	}

	//
	// right_rotate
	//
	template<typename T, typename sprout::enabler_if<std::is_integral<T>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR T
	right_rotate(T x, std::size_t n) {
		return (x >> n) ^ (x << (sizeof(T) * CHAR_BIT - n));
	}
}	// namespace sprout

#endif // #ifndef SPROUT_BIT_ROTATE_HPP
