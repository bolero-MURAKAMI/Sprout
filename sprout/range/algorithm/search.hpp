/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2019 Bolero MURAKAMI
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
					sprout::begin(SPROUT_FORWARD(ForwardRange1, range1)),
					sprout::end(SPROUT_FORWARD(ForwardRange1, range1)),
					sprout::begin(SPROUT_FORWARD(ForwardRange2, range2)),
					sprout::end(SPROUT_FORWARD(ForwardRange2, range2))
					),
				SPROUT_FORWARD(ForwardRange1, range1)
				);
		}

		template<typename ForwardRange1, typename ForwardRange2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange1>::type
		search(ForwardRange1&& range1, ForwardRange2&& range2, BinaryPredicate pred) {
			return sprout::range::range_return<ForwardRange1>::pack(
				sprout::search(
					sprout::begin(SPROUT_FORWARD(ForwardRange1, range1)),
					sprout::end(SPROUT_FORWARD(ForwardRange1, range1)),
					sprout::begin(SPROUT_FORWARD(ForwardRange2, range2)),
					sprout::end(SPROUT_FORWARD(ForwardRange2, range2)),
					pred
					),
				SPROUT_FORWARD(ForwardRange1, range1)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange1, typename ForwardRange2>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange1, RetV>::type
		search(ForwardRange1&& range1, ForwardRange2&& range2) {
			return sprout::range::range_return<ForwardRange1, RetV>::pack(
				sprout::search(
					sprout::begin(SPROUT_FORWARD(ForwardRange1, range1)),
					sprout::end(SPROUT_FORWARD(ForwardRange1, range1)),
					sprout::begin(SPROUT_FORWARD(ForwardRange2, range2)),
					sprout::end(SPROUT_FORWARD(ForwardRange2, range2))
					),
				SPROUT_FORWARD(ForwardRange1, range1)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange1, typename ForwardRange2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange1, RetV>::type
		search(ForwardRange1&& range1, ForwardRange2&& range2, BinaryPredicate pred) {
			return sprout::range::range_return<ForwardRange1, RetV>::pack(
				sprout::search(
					sprout::begin(SPROUT_FORWARD(ForwardRange1, range1)),
					sprout::end(SPROUT_FORWARD(ForwardRange1, range1)),
					sprout::begin(SPROUT_FORWARD(ForwardRange2, range2)),
					sprout::end(SPROUT_FORWARD(ForwardRange2, range2)),
					pred
					),
				SPROUT_FORWARD(ForwardRange1, range1)
				);
		}

		//
		template<typename ForwardRange, typename Searcher>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		search(ForwardRange&& range, Searcher const& searcher) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::search(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					searcher
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange, typename Searcher>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		search(ForwardRange&& range, Searcher const& searcher) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::search(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					searcher
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_SEARCH_HPP
