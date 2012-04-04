#ifndef SPROUT_UTILITY_FORWARD_HPP
#define SPROUT_UTILITY_FORWARD_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// forward
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T&& forward(typename std::remove_reference<T>::type& t) SPROUT_NOEXCEPT {
		return static_cast<T&&>(t);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR T&& forward(typename std::remove_reference<T>::type&& t) SPROUT_NOEXCEPT = delete;
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_FORWARD_HPP
