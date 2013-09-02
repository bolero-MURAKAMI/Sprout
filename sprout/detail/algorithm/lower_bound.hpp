/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_ALGORITHM_LOWER_BOUND_HPP
#define SPROUT_DETAIL_ALGORITHM_LOWER_BOUND_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>

namespace sprout {
	namespace detail {
		template<typename ForwardIterator, typename T, typename Compare>
		inline SPROUT_CONSTEXPR ForwardIterator
		lower_bound(
			ForwardIterator first, typename std::iterator_traits<ForwardIterator>::difference_type len,
			T const& value, Compare comp
			)
		{
			return len == 0 ? first
				: comp(*sprout::next(first, len / 2), value)
					? sprout::detail::lower_bound(sprout::next(first, len / 2 + 1), len - (len / 2 + 1), value, comp)
				: sprout::detail::lower_bound(first, len / 2, value, comp)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_LOWER_BOUND_HPP
