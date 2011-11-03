#ifndef SPROUT_UTILITY_MOVE_HPP
#define SPROUT_UTILITY_MOVE_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// move
	//
	template<typename T>
	SPROUT_CONSTEXPR typename std::remove_reference<T>::type&& move(T&& t) SPROUT_NOEXCEPT {
		return static_cast<typename std::remove_reference<T>::type&&>(t);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_MOVE_HPP
