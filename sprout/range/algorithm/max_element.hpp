/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_MAX_ELEMENT_HPP
#define SPROUT_RANGE_ALGORITHM_MAX_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/max_element.hpp>

namespace sprout {
	namespace range {

		// 25.4.7 Minimum and maximum
		template<typename ForwardRange>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		max_element(ForwardRange&& range) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::max_element(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range))
					),
				sprout::forward<ForwardRange>(range)
				);
		}

		template<typename ForwardRange, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		max_element(ForwardRange&& range, Compare comp) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::max_element(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range)),
					comp
					),
				sprout::forward<ForwardRange>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		max_element(ForwardRange&& range) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::max_element(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range))
					),
				sprout::forward<ForwardRange>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		max_element(ForwardRange&& range, Compare comp) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::max_element(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range)),
					comp
					),
				sprout::forward<ForwardRange>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_MAX_ELEMENT_HPP
