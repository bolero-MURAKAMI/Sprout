/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_REPLACE_COPY_HPP
#define SPROUT_ALGORITHM_REPLACE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// 25.3.5 Replace
	//
	template<
		typename InputIterator, typename OutputIterator, typename T,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR void
	replace_copy(InputIterator first, InputIterator last, OutputIterator result, T const& old_value, T const& new_value) {
		for (; first != last; ++first) {
			*result++ = (*first == old_value ? new_value : *first);
		}
		return result;
	}
}	// namespace sprout

#include <sprout/algorithm/fixed/replace_copy.hpp>
#include <sprout/algorithm/fit/replace_copy.hpp>

#endif	// #ifndef SPROUT_ALGORITHM_REPLACE_COPY_HPP
