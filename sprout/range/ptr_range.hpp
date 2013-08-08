/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_PTR_RANGE_HPP
#define SPROUT_RANGE_PTR_RANGE_HPP

#include <cstddef>
#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace range {
		//
		// make_ptr_range
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::range::range_container<sprout::ptr_index_iterator<T, true> >
		make_ptr_range(T* p, typename std::iterator_traits<T*>::difference_type n) {
			return sprout::range::range_container<sprout::ptr_index_iterator<T, true> >(
				sprout::ptr_index_iterator<T, true>(p),
				sprout::ptr_index_iterator<T, true>(p, n)
				);
		}

		template<typename T>
		inline SPROUT_CONSTEXPR sprout::range::range_container<sprout::ptr_index_iterator<T, true> >
		make_ptr_range(T* first, T* last) {
			return sprout::range::range_container<sprout::ptr_index_iterator<T, true> >(
				sprout::ptr_index_iterator<T, true>(first),
				sprout::ptr_index_iterator<T, true>(first, sprout::distance(first, last))
				);
		}

		template<typename T, std::size_t N>
		inline SPROUT_CONSTEXPR sprout::range::range_container<sprout::ptr_index_iterator<T, true> >
		make_ptr_range(T (& arr)[N]) {
			return sprout::range::range_container<sprout::ptr_index_iterator<T, true> >(
				sprout::ptr_index_iterator<T, true>(arr),
				sprout::ptr_index_iterator<T, true>(arr, N)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_PTR_RANGE_HPP
