/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_CLAMP_RANGE_HPP
#define SPROUT_ALGORITHM_CXX14_CLAMP_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/clamp.hpp>

namespace sprout {
	//
	// clamp_range
	//
	template<
		typename InputIterator, typename OutputIterator, typename Compare,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	clamp_range(
		InputIterator first, InputIterator last, OutputIterator result,
		typename std::iterator_traits<InputIterator>::value_type const& low,
		typename std::iterator_traits<InputIterator>::value_type const& high,
		Compare comp
		)
	{
		while (first != last) {
			*result++ = sprout::clamp(*first++, low, high, comp);
		}
		return result;
	}
	template<
		typename InputIterator, typename OutputIterator,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	clamp_range(
		InputIterator first, InputIterator last, OutputIterator result,
		typename std::iterator_traits<InputIterator>::value_type const& low,
		typename std::iterator_traits<InputIterator>::value_type const& high
		)
	{
		while (first != last) {
			*result++ = sprout::clamp(*first++, low, high);
		}
		return result;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_CLAMP_RANGE_HPP
