#ifndef SPROUT_MATH_CONSTANTS_HPP
#define SPROUT_MATH_CONSTANTS_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace math {
		//
		// pi
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T pi() {
			return 3.141592653589793238462643383279502884197169399375105820974944L;
		}
		//
		// pi_div_two
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T pi_div_two() {
			return 1.570796326794896619231321691639751442098584699687552910487472L;
		}
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CONSTANTS_HPP
