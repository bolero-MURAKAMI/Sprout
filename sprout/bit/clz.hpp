#ifndef SPROUT_BIT_CLZ_HPP
#define SPROUT_BIT_CLZ_HPP

#include <climits>
#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
#	if SPROUT_USE_BUILTIN_BIT_OPERATION
		inline SPROUT_CONSTEXPR int
		clz(unsigned n) {
			return __builtin_clz(n);
		}
		inline SPROUT_CONSTEXPR int
		clz(unsigned long n) {
			return __builtin_clzl(n);
		}
		inline SPROUT_CONSTEXPR int
		clz(unsigned long long n) {
			return __builtin_clzll(n);
		}
#	endif
		template<typename T>
		inline SPROUT_CONSTEXPR int
		clz_impl(T n, T m = T(1) << (CHAR_BIT * sizeof(T) - 1)) {
			return m == 0 || n & m ? 0
				: 1 + sprout::detail::clz_impl(n, static_cast<T>(m >> 1))
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_unsigned<T>::value,
			int
		>::type
		clz(T n) {
			return sprout::detail::clz_impl(static_cast<T>(n));
		}
		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_signed<T>::value,
			int
		>::type
		clz(T n) {
			return sprout::detail::clz(static_cast<typename std::make_unsigned<T>::type>(n));
		}
	}	// namespace detail
	//
	// clz
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<T>::value,
		int
	>::type
	clz(T n) {
		return sprout::detail::clz(n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_CLZ_HPP
