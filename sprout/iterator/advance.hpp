/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_ADVANCE_HPP
#define SPROUT_ITERATOR_ADVANCE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/assert.hpp>
#include <sprout/math/greater_equal.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator, typename Distance>
		inline SPROUT_CXX14_CONSTEXPR void
		advance_impl(InputIterator& it, Distance n, std::input_iterator_tag*) {
			SPROUT_ASSERT(sprout::math::greater_equal(n, 0));
			for (; 0 < n; --n) {
				++it;
			}
		}
		template<typename BidirectionalIterator, typename Distance>
		inline SPROUT_CXX14_CONSTEXPR void
		advance_impl(BidirectionalIterator& it, Distance n, std::bidirectional_iterator_tag*) {
			if (n > 0) {
				for (; 0 < n; --n) {
					++it;
				}
			} else {
				for (; n < 0; ++n) {
					--it;
				}
			}
		}
		template<typename RandomAccessIterator, typename Distance>
		inline SPROUT_CXX14_CONSTEXPR void
		advance_impl(RandomAccessIterator& it, Distance n, std::random_access_iterator_tag*) {
			it += n;
		}
	}	// namespace detail
	//
	// advance
	//
	template<typename Iterator, typename Distance>
	inline SPROUT_CXX14_CONSTEXPR void
	advance(Iterator& it, Distance n) {
		typedef typename std::iterator_traits<Iterator>::iterator_category* category;
		sprout::detail::advance_impl(it, n, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_ADVANCE_HPP
