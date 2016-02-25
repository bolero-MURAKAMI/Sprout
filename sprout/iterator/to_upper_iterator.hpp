/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_TO_UPPER_ITERATOR_HPP
#define SPROUT_ITERATOR_TO_UPPER_ITERATOR_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/transform_iterator.hpp>
#include <sprout/ctype/functor.hpp>

namespace sprout {
	//
	// make_to_upper_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::transform_iterator<sprout::ctypes::to_upper<typename std::iterator_traits<Iterator>::value_type>, Iterator>
	make_to_upper_iterator(Iterator it) {
		return sprout::transform_iterator<sprout::ctypes::to_upper<typename std::iterator_traits<Iterator>::value_type>, Iterator>(
			it, sprout::ctypes::to_upper<typename std::iterator_traits<Iterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_TO_UPPER_ITERATOR_HPP
