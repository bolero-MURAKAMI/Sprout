#ifndef SPROUT_RANGE_NUMERIC_ACCUMLATE_HPP
#define SPROUT_RANGE_NUMERIC_ACCUMLATE_HPP

#include <sprout/config.hpp>
#include <sprout/numeric/accumulate.hpp>

namespace sprout {
	// 26.7.2 Accumulate
	template<typename Range, typename T, typename BinaryOperation>
	inline SPROUT_CONSTEXPR T accumulate(Range const& range, T init, BinaryOperation binary_op) {
		return sprout::accumulate(sprout::begin(range), sprout::end(range), init, binary_op);
	}

	template<typename Range, typename T>
	inline SPROUT_CONSTEXPR T accumulate(Range const& range, T init) {
		return sprout::accumulate(sprout::begin(range), sprout::end(range), init);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_ACCUMLATE_HPP
