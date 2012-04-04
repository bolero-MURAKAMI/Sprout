#ifndef SPROUT_UTILITY_AS_LVREF_HPP
#define SPROUT_UTILITY_AS_LVREF_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// as_lvref
	//
	template<typename T>
	inline T& as_lvref(T& t) {
		return t;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR T const& as_lvref(T const& t) {
		return t;
	}

	//
	// lvref
	//
	template<typename T>
	struct lvref {
	public:
		typedef decltype(sprout::as_lvref(std::declval<T&&>())) type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_AS_LVREF_HPP
