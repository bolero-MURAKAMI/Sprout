/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_STR_HPP
#define SPROUT_DETAIL_STR_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR InputIterator
		str_find_check(InputIterator const& found) {
			return !*found ? InputIterator()
				: found
				;
		}

		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR InputIterator
		str_find_check(InputIterator const& found, T const& value) {
			return !(*found == value) && !*found ? InputIterator()
				: found
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_STR_HPP
