#ifndef SPROUT_OPTIONAL_MAKE_OPTIONAL_HPP
#define SPROUT_OPTIONAL_MAKE_OPTIONAL_HPP

#include <sprout/config.hpp>
#include <sprout/optional/optional.hpp>

namespace sprout {
	//
	// make_optional
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::optional<T>
	make_optional(T const& v) {
		return optional<T>(v);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::optional<T>
	make_optional(bool cond, T const& v) {
		return optional<T>(cond, v);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_MAKE_OPTIONAL_HPP
