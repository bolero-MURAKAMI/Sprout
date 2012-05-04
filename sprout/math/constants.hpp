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
		//
		// root_two
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T root_two() {
			return 1.414213562373095048801688724209698078569671875376948073L;
		}
		//
		// half_root_two
		//
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
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T ln_ten() {
			return 2.302585092994045684017991454684364207601101488628772976L;
		}
		//
		// ln_two
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T ln_two() {
			return 0.693147180559945309417232121458176568075500134360255254L;
		}
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CONSTANTS_HPP
