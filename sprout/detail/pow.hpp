#ifndef SPROUT_DETAIL_POW_HPP
#define SPROUT_DETAIL_POW_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR T
		pow2(T const& x) {
			return x * x;
		}

		template<typename T>
		inline SPROUT_CONSTEXPR T
		pow3(T const& x) {
			return x * x * x;
		}

		template<typename T>
		inline SPROUT_CONSTEXPR T
		pow_n_impl(T const& x, int n) {
			return n == 1 ? x
				: n % 2 ? x * sprout::detail::pow2(sprout::detail::pow_n_impl(x, n / 2))
				: sprout::detail::pow2(sprout::detail::pow_n_impl(x, n / 2))
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T
		pow_n(T const& x, int n) {
			return n == 0 ? T(1)
				: sprout::detail::pow_n_impl(x, n)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_POW_HPP
