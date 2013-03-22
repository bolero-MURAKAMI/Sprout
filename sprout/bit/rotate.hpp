#ifndef SPROUT_BIT_ROTATE_HPP
#define SPROUT_BIT_ROTATE_HPP

#include <cstddef>
#include <climits>
#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// left_rotate
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<T>::value,
		T
	>::type
	left_rotate(T x, std::size_t n) {
		return (x << n) ^ (x >> (sizeof(T) * CHAR_BIT - n));
	}

	//
	// right_rotate
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<T>::value,
		T
	>::type
	right_rotate(T x, std::size_t n) {
		return (x >> n) ^ (x << (sizeof(T) * CHAR_BIT - n));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_ROTATE_HPP
