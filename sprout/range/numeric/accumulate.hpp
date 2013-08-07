#ifndef SPROUT_RANGE_NUMERIC_ACCUMLATE_HPP
#define SPROUT_RANGE_NUMERIC_ACCUMLATE_HPP

#include <sprout/config.hpp>
#include <sprout/numeric/accumulate.hpp>

namespace sprout {
	namespace range {
		// 26.7.2 Accumulate
		template<typename InputRange, typename T, typename BinaryOperation>
		inline SPROUT_CONSTEXPR T
		accumulate(InputRange const& range, T init, BinaryOperation binary_op) {
			return sprout::accumulate(sprout::begin(range), sprout::end(range), init, binary_op);
		}

		template<typename InputRange, typename T>
		inline SPROUT_CONSTEXPR T
		accumulate(InputRange const& range, T init) {
			return sprout::accumulate(sprout::begin(range), sprout::end(range), init);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_ACCUMLATE_HPP
