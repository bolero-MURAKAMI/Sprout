/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_CLAMP_RANGE_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_CLAMP_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/clamp_range.hpp>

namespace sprout {
	namespace range {
		//
		// clamp_range
		//
		template<
			typename InputRange, typename OutputIterator, typename Compare,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CXX14_CONSTEXPR OutputIterator
		clamp_range(
			InputRange const& rng, OutputIterator result,
			typename sprout::container_traits<InputRange>::value_type const& low,
			typename sprout::container_traits<InputRange>::value_type const& high,
			Compare comp
			)
		{
			return sprout::clamp_range(sprout::begin(rng), sprout::end(rng), result, low, high, comp);
		}
		template<
			typename InputRange, typename OutputIterator,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CXX14_CONSTEXPR OutputIterator
		clamp_range(
			InputRange const& rng, OutputIterator result,
			typename sprout::container_traits<InputRange>::value_type const& low,
			typename sprout::container_traits<InputRange>::value_type const& high
			)
		{
			return sprout::clamp_range(sprout::begin(rng), sprout::end(rng), result, low, high);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_CLAMP_RANGE_HPP
