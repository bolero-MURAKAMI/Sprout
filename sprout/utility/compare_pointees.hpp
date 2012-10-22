#ifndef SPROUT_UTILITY_COMPARE_POINTEES_HPP
#define SPROUT_UTILITY_COMPARE_POINTEES_HPP

#include <sprout/config.hpp>
#include <sprout/functional/base.hpp>

namespace sprout {
	//
	// equal_pointees
	//
	template<class OptionalPointee>
	inline SPROUT_CONSTEXPR bool
	equal_pointees(OptionalPointee const& lhs, OptionalPointee const& rhs) {
		return (!lhs) != (!rhs) ? false : (!lhs ? true : (*lhs) == (*rhs));
	}
	//
	// less_pointees
	//
	template<class OptionalPointee>
	inline SPROUT_CONSTEXPR bool
	less_pointees(OptionalPointee const& lhs, OptionalPointee const& rhs) {
		return !rhs ? false : (!lhs ? true : (*lhs) < (*rhs));
	}

	//
	// equal_pointees_t
	//
	template<class OptionalPointee>
	struct equal_pointees_t
		: public sprout::binary_function<OptionalPointee, OptionalPointee, bool>
	{
		SPROUT_CONSTEXPR bool
		operator()(OptionalPointee const& lhs, OptionalPointee const& rhs) const {
			return sprout::equal_pointees(lhs, rhs) ;
		}
	} ;
	//
	// less_pointees_t
	//
	template<class OptionalPointee>
	struct less_pointees_t
		: public sprout::binary_function<OptionalPointee, OptionalPointee, bool>
	{
		SPROUT_CONSTEXPR bool
		operator()(OptionalPointee const& lhs, OptionalPointee const& rhs) const {
			return sprout::less_pointees(lhs, rhs) ;
		}
	} ;
}	// namespace sprout

#endif // #ifndef SPROUT_UTILITY_COMPARE_POINTEES_HPP
