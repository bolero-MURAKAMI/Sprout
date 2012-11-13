#ifndef SPROUT_UTILITY_ANY_CONVERTIBLE_HPP
#define SPROUT_UTILITY_ANY_CONVERTIBLE_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// any_convertible
	//
	struct any_convertible {
	public:
		template<typename T>
		SPROUT_CONSTEXPR operator T() const {
			return T();
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_ANY_CONVERTIBLE_HPP
