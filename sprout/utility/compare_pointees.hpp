#ifndef SPROUT_UTILITY_COMPARE_POINTEES_HPP
#define SPROUT_UTILITY_COMPARE_POINTEES_HPP

#include <sprout/config.hpp>
#include <sprout/functional/base.hpp>

namespace sprout {
	//
	// equal_pointees
	//
	template<typename OptionalPointee>
	inline SPROUT_CONSTEXPR bool
	equal_pointees(OptionalPointee const& lhs, OptionalPointee const& rhs) {
		return (!lhs) != (!rhs) ? false : (!lhs ? true : (*lhs) == (*rhs));
	}
	//
	// not_equal_pointees
	//
	template<typename OptionalPointee>
	inline SPROUT_CONSTEXPR bool
	not_equal_pointees(OptionalPointee const& lhs, OptionalPointee const& rhs) {
		return !sprout::equal_pointees(lhs, rhs);
	}
	//
	// less_pointees
	//
	template<typename OptionalPointee>
	inline SPROUT_CONSTEXPR bool
	less_pointees(OptionalPointee const& lhs, OptionalPointee const& rhs) {
		return !rhs ? false : (!lhs ? true : (*lhs) < (*rhs));
	}
	//
	// greater_pointees
	//
	template<typename OptionalPointee>
	inline SPROUT_CONSTEXPR bool
	greater_pointees(OptionalPointee const& lhs, OptionalPointee const& rhs) {
		return sprout::less_pointees(rhs, lhs);
	}
	//
	// less_equal_pointees
	//
	template<typename OptionalPointee>
	inline SPROUT_CONSTEXPR bool
	less_equal_pointees(OptionalPointee const& lhs, OptionalPointee const& rhs) {
		return !sprout::less_pointees(rhs, lhs);
	}
	//
	// greater_equal_pointees
	//
	template<typename OptionalPointee>
	inline SPROUT_CONSTEXPR bool
	greater_equal_pointees(OptionalPointee const& lhs, OptionalPointee const& rhs) {
		return !sprout::less_pointees(lhs, rhs);
	}

	//
	// equal_pointees_t
	//
	template<typename OptionalPointee>
	struct equal_pointees_t
		: public sprout::binary_function<OptionalPointee, OptionalPointee, bool>
	{
		SPROUT_CONSTEXPR bool
		operator()(OptionalPointee const& lhs, OptionalPointee const& rhs) const {
			return sprout::equal_pointees(lhs, rhs);
		}
	};
	//
	// not_equal_pointees_t
	//
	template<typename OptionalPointee>
	struct not_equal_pointees_t
		: public sprout::binary_function<OptionalPointee, OptionalPointee, bool>
	{
		SPROUT_CONSTEXPR bool
		operator()(OptionalPointee const& lhs, OptionalPointee const& rhs) const {
			return sprout::not_equal_pointees(lhs, rhs);
		}
	};
	//
	// less_pointees_t
	//
	template<typename OptionalPointee>
	struct less_pointees_t
		: public sprout::binary_function<OptionalPointee, OptionalPointee, bool>
	{
		SPROUT_CONSTEXPR bool
		operator()(OptionalPointee const& lhs, OptionalPointee const& rhs) const {
			return sprout::less_pointees(lhs, rhs);
		}
	};
	//
	// greater_pointees_t
	//
	template<typename OptionalPointee>
	struct greater_pointees_t
		: public sprout::binary_function<OptionalPointee, OptionalPointee, bool>
	{
		SPROUT_CONSTEXPR bool
		operator()(OptionalPointee const& lhs, OptionalPointee const& rhs) const {
			return sprout::greater_pointees(lhs, rhs);
		}
	};
	//
	// less_equal_pointees_t
	//
	template<typename OptionalPointee>
	struct less_equal_pointees_t
		: public sprout::binary_function<OptionalPointee, OptionalPointee, bool>
	{
		SPROUT_CONSTEXPR bool
		operator()(OptionalPointee const& lhs, OptionalPointee const& rhs) const {
			return sprout::less_equal_pointees(lhs, rhs);
		}
	};
	//
	// greater_equal_pointees_t
	//
	template<typename OptionalPointee>
	struct greater_equal_pointees_t
		: public sprout::binary_function<OptionalPointee, OptionalPointee, bool>
	{
		SPROUT_CONSTEXPR bool
		operator()(OptionalPointee const& lhs, OptionalPointee const& rhs) const {
			return sprout::greater_equal_pointees(lhs, rhs);
		}
	};
}	// namespace sprout

#endif // #ifndef SPROUT_UTILITY_COMPARE_POINTEES_HPP
