/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_NEXT_HPP
#define SPROUT_ITERATOR_NEXT_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/advance.hpp>
#include <sprout/iterator/next_fwd.hpp>
#include <sprout/iterator/prev_fwd.hpp>
#include <sprout/adl/not_found.hpp>
#include <sprout/assert.hpp>
#include <sprout/math/greater_equal.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl iterator_next(...);
}	// namespace sprout_adl

namespace sprout {
	namespace iterator_detail {
		template<typename InputIterator>
		inline SPROUT_CXX14_CONSTEXPR InputIterator
		cxx14_next(InputIterator it, typename std::iterator_traits<InputIterator>::difference_type n = 1) {
			sprout::advance(it, n);
			return it;
		}

		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		next_impl(RandomAccessIterator const& it, std::random_access_iterator_tag*) {
			return it + 1;
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR InputIterator
		next_impl(InputIterator const& it, std::input_iterator_tag*) {
			return sprout::iterator_detail::cxx14_next(it);
		}

		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		next_impl(
			RandomAccessIterator const& it, typename std::iterator_traits<RandomAccessIterator>::difference_type n,
			std::random_access_iterator_tag*
			)
		{
			return it + n;
		}

		template<typename BidirectionalIterator>
		inline SPROUT_CONSTEXPR BidirectionalIterator
		next_impl_2_neg(BidirectionalIterator const& it, typename std::iterator_traits<BidirectionalIterator>::difference_type n) {
			return n == -1 ? sprout::prev(it)
				: sprout::iterator_detail::next_impl_2_neg(
					sprout::iterator_detail::next_impl_2_neg(it, n / 2),
					n - (n / 2)
					)
				;
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR InputIterator
		next_impl_2(InputIterator const& it, typename std::iterator_traits<InputIterator>::difference_type n) {
			return n == 1 ? sprout::next(it)
				: sprout::iterator_detail::next_impl_2(
					sprout::iterator_detail::next_impl_2(it, n / 2),
					n - (n / 2)
					)
				;
		}

		template<typename BidirectionalIterator>
		inline SPROUT_CONSTEXPR BidirectionalIterator
		next_impl_1(
			BidirectionalIterator const& it, typename std::iterator_traits<BidirectionalIterator>::difference_type n,
			std::bidirectional_iterator_tag*
			)
		{
			return n == 0 ? it
				: n > 0 ? sprout::iterator_detail::next_impl_2(it, n)
				: sprout::iterator_detail::next_impl_2_neg(it, n)
				;
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR InputIterator
		next_impl_1(
			InputIterator const& it, typename std::iterator_traits<InputIterator>::difference_type n,
			std::input_iterator_tag*
			)
		{
			return SPROUT_ASSERT(sprout::math::greater_equal(n, 0)),
				n == 0 ? it
					: sprout::iterator_detail::next_impl_2(it, n)
				;
		}

		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<InputIterator>::value,
			InputIterator
		>::type
		next_impl(
			InputIterator const& it, typename std::iterator_traits<InputIterator>::difference_type n,
			std::input_iterator_tag*
			)
		{
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::iterator_detail::next_impl_1(it, n, category());
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!std::is_literal_type<InputIterator>::value,
			InputIterator
		>::type
		next_impl(
			InputIterator const& it, typename std::iterator_traits<InputIterator>::difference_type n,
			std::input_iterator_tag*
			)
		{
			return sprout::iterator_detail::cxx14_next(it, n);
		}

		template<typename InputIterator>
		inline SPROUT_CONSTEXPR InputIterator
		iterator_next(InputIterator const& it) {
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::iterator_detail::next_impl(it, category());
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR InputIterator
		iterator_next(InputIterator const& it, typename std::iterator_traits<InputIterator>::difference_type n) {
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::iterator_detail::next_impl(it, n, category());
		}
	}	// namespace iterator_detail
}	// namespace sprout

namespace sprout_iterator_detail {
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR InputIterator
	next(InputIterator const& it) {
		using sprout::iterator_detail::iterator_next;
		using sprout_adl::iterator_next;
		return iterator_next(it);
	}
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR InputIterator
	next(InputIterator const& it, typename std::iterator_traits<InputIterator>::difference_type n) {
		using sprout::iterator_detail::iterator_next;
		using sprout_adl::iterator_next;
		return iterator_next(it, n);
	}
}	// namespace sprout_iterator_detail

namespace sprout {
	//
	// next
	//
	//	effect:
	//		ADL callable iterator_next(it) -> iterator_next(it)
	//		otherwise, InputIterator is RandomAccessIterator -> it + 1
	//		otherwise -> cxx14_next(it)
	//
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR InputIterator
	next(InputIterator const& it) {
		return sprout_iterator_detail::next(it);
	}
	//
	//	effect:
	//		ADL callable iterator_next(it, n) -> iterator_next(it, n)
	//		it is RandomAccessIterator -> it + n
	//		it is LiteralType && n >= 0 -> sprout::next(it)...
	//		it is LiteralType && n < 0 -> sprout::prev(it)...
	//		otherwise -> cxx14_next(it, n)
	//
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR InputIterator
	next(InputIterator const& it, typename std::iterator_traits<InputIterator>::difference_type n) {
		return sprout_iterator_detail::next(it, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_NEXT_HPP
