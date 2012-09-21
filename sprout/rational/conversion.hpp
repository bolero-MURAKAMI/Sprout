#ifndef SPROUT_RATIONAL_CONVERSION_HPP
#define SPROUT_RATIONAL_CONVERSION_HPP

#include <sprout/config.hpp>
#include <sprout/rational/rational.hpp>

namespace sprout {
	//
	// rational_cast
	//
	template<typename T, typename IntType>
	inline SPROUT_CONSTEXPR T
	rational_cast(sprout::rational<IntType> const& src) {
		return static_cast<T>(src.numerator()) / static_cast<T>(src.denominator());
	}
} // namespace sprout

#endif	// SPROUT_RATIONAL_CONVERSION_HPP
