#ifndef SPROUT_RANGE_NUMERIC_INNER_PRODUCT_HPP
#define SPROUT_RANGE_NUMERIC_INNER_PRODUCT_HPP

#include <sprout/config.hpp>
#include <sprout/numeric/inner_product.hpp>

namespace sprout {
	namespace range {
		// 26.7.3 Inner product
		template<typename Range1, typename Range2, typename T, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR T
		inner_product(
			Range1 const& range1, Range2 const& range2, T init,
			BinaryOperation1 binary_op1, BinaryOperation2 binary_op2
			)
		{
			return sprout::inner_product(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), init, binary_op1, binary_op2);
		}

		template<typename Range1, typename Range2, typename T>
		inline SPROUT_CONSTEXPR T
		inner_product(Range1 const& range1, Range2 const& range2, T init) {
			return sprout::inner_product(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), init);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_INNER_PRODUCT_HPP
