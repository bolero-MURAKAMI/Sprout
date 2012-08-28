#ifndef SPROUT_RATIONAL_VALUES_HPP
#define SPROUT_RATIONAL_VALUES_HPP

#include <sprout/config.hpp>
#include <sprout/rational/rational.hpp>
#include <sprout/cstdlib/abs.hpp>

namespace sprout {
	//
	// abs
	//
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	abs(sprout::rational<IntType> const& x) {
		return x.numerator() >= IntType(0) ? x
			: sprout::detail::make_rational<IntType>(
				-x.numerator(), x.denominator(),
				sprout::detail::rational_private_constructor_tag()
				)
			;
	}
} // namespace sprout

#endif  // SPROUT_RATIONAL_VALUES_HPP
