#ifndef SPROUT_OPTIONAL_MAKE_OPTIONAL_HPP
#define SPROUT_OPTIONAL_MAKE_OPTIONAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/optional/optional.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// make_optional
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::optional<typename std::decay<T>::type>
	make_optional(T&& v) {
		return sprout::optional<typename std::decay<T>::type>(sprout::forward<T>(v));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::optional<typename std::decay<T>::type>
	make_optional(bool cond, T&& v) {
		return sprout::optional<typename std::decay<T>::type>(cond, sprout::forward<T>(v));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_MAKE_OPTIONAL_HPP
