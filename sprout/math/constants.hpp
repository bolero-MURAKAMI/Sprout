#ifndef SPROUT_MATH_CONSTANTS_HPP
#define SPROUT_MATH_CONSTANTS_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace math {
		//
		// pi
		// half_pi
		// quarter_pi
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T pi() {
			return 3.141592653589793238462643383279502884197169399375105820974944L;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T half_pi() {
			return 1.570796326794896619231321691639751442098584699687552910487472L;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T quarter_pi() {
			return 0.785398163397448309615660845819875721049292349843776455243736L;
		}
		//
		// half
		// third
		// twothirds
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T half() {
			return 0.5L;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T third() {
			return 0.3333333333333333333333333333333333333333333333333333333333333333333333L;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T twothirds() {
			return 0.6666666666666666666666666666666666666666666666666666666666666666666666L;
		}
		//
		// root_two
		// half_root_two
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T root_two() {
			return 1.414213562373095048801688724209698078569671875376948073L;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T half_root_two() {
			return 0.70710678118654752440084436210484903928483593756084L;
		}
		//
		// e
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T e() {
			return 2.7182818284590452353602874713526624977572470936999595749669676L;
		}
		//
		// ln_ten
		// ln_two
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T ln_ten() {
			return 2.302585092994045684017991454684364207601101488628772976L;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T ln_two() {
			return 0.693147180559945309417232121458176568075500134360255254L;
		}
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CONSTANTS_HPP
