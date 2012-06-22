#ifndef SPROUT_BIT_POPCOUNT_HPP
#define SPROUT_BIT_POPCOUNT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace detail {
#	if SPROUT_USE_BUILTIN_BIT_OPERATION
		inline SPROUT_CONSTEXPR int
		popcount(unsigned n) {
			return __builtin_popcount(n);
		}
		inline SPROUT_CONSTEXPR int
		popcount(unsigned long n) {
			return __builtin_popcountl(n);
		}
		inline SPROUT_CONSTEXPR int
		popcount(unsigned long long n) {
			return __builtin_popcountll(n);
		}
#	endif
		template<typename T, typename sprout::enabler_if<std::is_unsigned<T>::value>::type = sprout::enabler>
		inline SPROUT_CONSTEXPR int
		popcount(T n) {
			return n == 0 ? 0
				: 1 + sprout::detail::popcount(static_cast<T>(n & (n - 1)))
				;
		}
		template<typename T, typename sprout::enabler_if<std::is_signed<T>::value>::type = sprout::enabler>
		inline SPROUT_CONSTEXPR int
		popcount(T n) {
			return sprout::detail::popcount(static_cast<typename std::make_unsigned<T>::type>(n));
		}
	}	// namespace detail
	//
	// popcount
	//
	template<typename T, typename sprout::enabler_if<std::is_integral<T>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR int
	popcount(T n) {
		return sprout::detail::popcount(n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_POPCOUNT_HPP
