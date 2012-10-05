#ifndef SPROUT_UTILITY_REL_OPS_HPP
#define SPROUT_UTILITY_REL_OPS_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace rel_ops {
		template <typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(T const& x, T const& y) {
			return !(x == y);
		}

		template <typename T>
		inline SPROUT_CONSTEXPR bool
		operator>(T const& x, T const& y) {
			return y < x;
		}

		template <typename T>
		inline SPROUT_CONSTEXPR bool
		operator<=(T const& x, T const& y) {
			return !(y < x);
		}

		template <typename T>
		inline SPROUT_CONSTEXPR bool
		operator>=(T const& x, T const& y) {
			return !(x < y);
		}
	}	// namespace rel_ops
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_REL_OPS_HPP
