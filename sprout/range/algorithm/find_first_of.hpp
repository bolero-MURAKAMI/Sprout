#ifndef SPROUT_RANGE_ALGORITHM_FIND_FIRST_OF_HPP
#define SPROUT_RANGE_ALGORITHM_FIND_FIRST_OF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/find_first_of.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.7 Find first
		template<typename InputRange1, typename InputRange2>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<InputRange1>::type
		find_first_of(InputRange1&& range1, InputRange2&& range2) {
			return sprout::range::range_return<InputRange1>::pack(
				sprout::find_first_of(
					sprout::begin(sprout::forward<InputRange1>(range1)),
					sprout::end(sprout::forward<InputRange1>(range1)),
					sprout::begin(sprout::forward<InputRange2>(range2)),
					sprout::end(sprout::forward<InputRange2>(range2))
					),
				sprout::forward<InputRange1>(range1)
				);
		}

		template<typename InputRange1, typename InputRange2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<InputRange1>::type
		find_first_of(InputRange1&& range1, InputRange2&& range2, BinaryPredicate pred) {
			return sprout::range::range_return<InputRange1>::pack(
				sprout::find_first_of(
					sprout::begin(sprout::forward<InputRange1>(range1)),
					sprout::end(sprout::forward<InputRange1>(range1)),
					sprout::begin(sprout::forward<InputRange2>(range2)),
					sprout::end(sprout::forward<InputRange2>(range2)),
					pred
					),
				sprout::forward<InputRange1>(range1)
				);
		}

		template<sprout::range::range_return_value RetV, typename InputRange1, typename InputRange2>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<InputRange1, RetV>::type
		find_first_of(InputRange1&& range1, InputRange2&& range2) {
			return sprout::range::range_return<InputRange1, RetV>::pack(
				sprout::find_first_of(
					sprout::begin(sprout::forward<InputRange1>(range1)),
					sprout::end(sprout::forward<InputRange1>(range1)),
					sprout::begin(sprout::forward<InputRange2>(range2)),
					sprout::end(sprout::forward<InputRange2>(range2))
					),
				sprout::forward<InputRange1>(range1)
				);
		}

		template<sprout::range::range_return_value RetV, typename InputRange1, typename InputRange2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<InputRange1, RetV>::type
		find_first_of(InputRange1&& range1, InputRange2&& range2, BinaryPredicate pred) {
			return sprout::range::range_return<InputRange1, RetV>::pack(
				sprout::find_first_of(
					sprout::begin(sprout::forward<InputRange1>(range1)),
					sprout::end(sprout::forward<InputRange1>(range1)),
					sprout::begin(sprout::forward<InputRange2>(range2)),
					sprout::end(sprout::forward<InputRange2>(range2)),
					pred
					),
				sprout::forward<InputRange1>(range1)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIND_FIRST_OF_HPP
