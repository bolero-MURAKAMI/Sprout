#ifndef SPROUT_RANGE_ALGORITHM_FIND_HPP
#define SPROUT_RANGE_ALGORITHM_FIND_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/operation.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/find.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.5 Find
		template<typename Range, typename T>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range>::type
		find(Range&& range, T const& value) {
			return sprout::range::range_return<Range>::pack(
				sprout::find(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					value
					),
				sprout::forward<Range>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range, typename T>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range, RetV>::type
		find(Range&& range, T const& value) {
			return sprout::range::range_return<Range, RetV>::pack(
				sprout::find(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					value
					),
				sprout::forward<Range>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIND_HPP
