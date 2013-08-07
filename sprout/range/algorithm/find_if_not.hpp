#ifndef SPROUT_RANGE_ALGORITHM_FIND_IF_NOT_HPP
#define SPROUT_RANGE_ALGORITHM_FIND_IF_NOT_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/find_if_not.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.5 Find
		template<typename InputRange, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<InputRange>::type
		find_if_not(InputRange&& range, Predicate pred) {
			return sprout::range::range_return<InputRange>::pack(
				sprout::find_if_not(
					sprout::begin(sprout::forward<InputRange>(range)),
					sprout::end(sprout::forward<InputRange>(range)),
					pred
					),
				sprout::forward<InputRange>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename InputRange, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<InputRange, RetV>::type
		find_if_not(InputRange&& range, Predicate pred) {
			return sprout::range::range_return<InputRange, RetV>::pack(
				sprout::find_if_not(
					sprout::begin(sprout::forward<InputRange>(range)),
					sprout::end(sprout::forward<InputRange>(range)),
					pred
					),
				sprout::forward<InputRange>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIND_IF_NOT_HPP
