/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_SEARCH_HPP
#define SPROUT_RANGE_ALGORITHM_SEARCH_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/search.hpp>

namespace sprout {
	namespace range {

		// 25.2.13 Search
		template<typename ForwardRange1, typename ForwardRange2>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange1>::type
		search(ForwardRange1&& range1, ForwardRange2&& range2) {
			return sprout::range::range_return<ForwardRange1>::pack(
				sprout::search(
					sprout::begin(sprout::forward<ForwardRange1>(range1)),
					sprout::end(sprout::forward<ForwardRange1>(range1)),
					sprout::begin(sprout::forward<ForwardRange2>(range2)),
					sprout::end(sprout::forward<ForwardRange2>(range2))
					),
				sprout::forward<ForwardRange1>(range1)
				);
		}

		template<typename ForwardRange1, typename ForwardRange2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange1>::type
		search(ForwardRange1&& range1, ForwardRange2&& range2, BinaryPredicate pred) {
			return sprout::range::range_return<ForwardRange1>::pack(
				sprout::search(
					sprout::begin(sprout::forward<ForwardRange1>(range1)),
					sprout::end(sprout::forward<ForwardRange1>(range1)),
					sprout::begin(sprout::forward<ForwardRange2>(range2)),
					sprout::end(sprout::forward<ForwardRange2>(range2)),
					pred
					),
				sprout::forward<ForwardRange1>(range1)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange1, typename ForwardRange2>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange1, RetV>::type
		search(ForwardRange1&& range1, ForwardRange2&& range2) {
			return sprout::range::range_return<ForwardRange1, RetV>::pack(
				sprout::search(
					sprout::begin(sprout::forward<ForwardRange1>(range1)),
					sprout::end(sprout::forward<ForwardRange1>(range1)),
					sprout::begin(sprout::forward<ForwardRange2>(range2)),
					sprout::end(sprout::forward<ForwardRange2>(range2))
					),
				sprout::forward<ForwardRange1>(range1)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange1, typename ForwardRange2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange1, RetV>::type
		search(ForwardRange1&& range1, ForwardRange2&& range2, BinaryPredicate pred) {
			return sprout::range::range_return<ForwardRange1, RetV>::pack(
				sprout::search(
					sprout::begin(sprout::forward<ForwardRange1>(range1)),
					sprout::end(sprout::forward<ForwardRange1>(range1)),
					sprout::begin(sprout::forward<ForwardRange2>(range2)),
					sprout::end(sprout::forward<ForwardRange2>(range2)),
					pred
					),
				sprout::forward<ForwardRange1>(range1)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_SEARCH_HPP
