#ifndef SPROUT_RANGE_ALGORITHM_SEARCH_N_HPP
#define SPROUT_RANGE_ALGORITHM_SEARCH_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/operation.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/search_n.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.13 Search
		template<typename Range, typename Size, typename T>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range>::type
		search_n(Range&& range, Size count, T const& value) {
			return sprout::range::range_return<Range>::pack(
				sprout::search_n(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					count,
					value
					),
				sprout::forward<Range>(range)
				);
		}

		template<typename Range, typename Size, typename T, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range>::type
		search_n(Range&& range, Size count, T const& value, BinaryPredicate pred) {
			return sprout::range::range_return<Range>::pack(
				sprout::search_n(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					count,
					value,
					pred
					),
				sprout::forward<Range>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range, typename Size, typename T>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range, RetV>::type
		search_n(Range&& range, Size count, T const& value) {
			return sprout::range::range_return<Range, RetV>::pack(
				sprout::search_n(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					count,
					value
					),
				sprout::forward<Range>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range, typename Size, typename T, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range, RetV>::type
		search_n(Range&& range, Size count, T const& value, BinaryPredicate pred) {
			return sprout::range::range_return<Range, RetV>::pack(
				sprout::search_n(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					count,
					value,
					pred
					),
				sprout::forward<Range>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_SEARCH_N_HPP
