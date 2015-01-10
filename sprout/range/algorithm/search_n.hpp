/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_SEARCH_N_HPP
#define SPROUT_RANGE_ALGORITHM_SEARCH_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/search_n.hpp>

namespace sprout {
	namespace range {

		// 25.2.13 Search
		template<typename ForwardRange, typename Size, typename T>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		search_n(ForwardRange&& range, Size count, T const& value) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::search_n(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					count,
					value
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}

		template<typename ForwardRange, typename Size, typename T, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		search_n(ForwardRange&& range, Size count, T const& value, BinaryPredicate pred) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::search_n(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					count,
					value,
					pred
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange, typename Size, typename T>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		search_n(ForwardRange&& range, Size count, T const& value) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::search_n(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					count,
					value
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange, typename Size, typename T, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		search_n(ForwardRange&& range, Size count, T const& value, BinaryPredicate pred) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::search_n(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					count,
					value,
					pred
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_SEARCH_N_HPP
