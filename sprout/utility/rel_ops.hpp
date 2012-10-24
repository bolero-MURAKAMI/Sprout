#ifndef SPROUT_UTILITY_REL_OPS_HPP
#define SPROUT_UTILITY_REL_OPS_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace rel_ops {
		//
		// operator!=
		//
		template <typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(T const& x, T const& y) {
			return !(x == y);
		}
		//
		// operator>
		//
		template <typename T>
		inline SPROUT_CONSTEXPR bool
		operator>(T const& x, T const& y) {
			return y < x;
		}
		//
		// operator<=
		//
		template <typename T>
		inline SPROUT_CONSTEXPR bool
		operator<=(T const& x, T const& y) {
			return !(y < x);
		}
		//
		// operator>=
		//
		template <typename T>
		inline SPROUT_CONSTEXPR bool
		operator>=(T const& x, T const& y) {
			return !(x < y);
		}
	}	// namespace rel_ops
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_REL_OPS_HPP
