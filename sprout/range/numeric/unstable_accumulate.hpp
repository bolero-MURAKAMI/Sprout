#ifndef SPROUT_RANGE_NUMERIC_UNSTABLE_ACCUMLATE_HPP
#define SPROUT_RANGE_NUMERIC_UNSTABLE_ACCUMLATE_HPP

#include <sprout/config.hpp>
#include <sprout/numeric/unstable_accumulate.hpp>

namespace sprout {
	namespace range {
		//
		// unstable_accumulate
		//
		template<typename Range, typename T, typename BinaryOperation>
		inline SPROUT_CONSTEXPR T
		unstable_accumulate(Range const& range, T init, BinaryOperation binary_op) {
			return sprout::unstable_accumulate(sprout::begin(range), sprout::end(range), init, binary_op);
		}

		template<typename Range, typename T>
		inline SPROUT_CONSTEXPR T
		unstable_accumulate(Range const& range, T init) {
			return sprout::unstable_accumulate(sprout::begin(range), sprout::end(range), init);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_UNSTABLE_ACCUMLATE_HPP
