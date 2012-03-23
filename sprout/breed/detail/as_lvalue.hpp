#ifndef SPROUT_BREED_DETAIL_AS_LVALUE_HPP
#define SPROUT_BREED_DETAIL_AS_LVALUE_HPP

#include <sprout/config.hpp>
#include <sprout/breed/breed_fwd.hpp>

namespace sprout {
	namespace breed {
		namespace detail {
			template<typename T>
			SPROUT_CONSTEXPR T& as_lvalue(T& t) {
				return t;
			}
			template<typename T>
			SPROUT_CONSTEXPR T const& as_lvalue(T const& t) {
				return t;
			}
		}	// namespace detail
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_DETAIL_AS_LVALUE_HPP
