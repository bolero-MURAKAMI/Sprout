#ifndef SPROUT_RANGE_ALGORITHM_FIND_IF_NOT_HPP
#define SPROUT_RANGE_ALGORITHM_FIND_IF_NOT_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/operation.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/find_if_not.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.5 Find
		template<typename Range, typename Predicate>
		SPROUT_CONSTEXPR typename sprout::range::range_return<Range>::type
		find_if_not(Range&& range, Predicate pred) {
			return sprout::range::range_return<Range>::pack(
				sprout::find_if_not(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					pred
					),
				sprout::forward<Range>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range, typename Predicate>
		SPROUT_CONSTEXPR typename sprout::range::range_return<Range, RetV>::type
		find_if_not(Range&& range, Predicate pred) {
			return sprout::range::range_return<Range, RetV>::pack(
				sprout::find_if_not(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					pred
					),
				sprout::forward<Range>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIND_IF_NOT_HPP
