/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TESTSPR_ALGORITHM_HPP
#define TESTSPR_ALGORITHM_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/container.hpp>

namespace testspr {
	//
	// distance
	//
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		return first == last ? 0
			: 1 + testspr::distance(first + 1, last)
			;
	}

	//
	// equal
	//
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR bool
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		return first1 == last1 ? first2 == last2
			: first2 == last2 ? false
			: !(*first1 == *first2) ? false
			: testspr::equal(first1 + 1, last1, first2 + 1, last2)
			;
	}
	template<typename InputRange1, typename InputRange2>
	inline SPROUT_CONSTEXPR bool
	equal(InputRange1 const& range1, InputRange2 const& range2) {
		return testspr::equal(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2));
	}

	//
	// is_found
	//
	template<class InputIterator, typename T>
	inline SPROUT_CONSTEXPR bool
	is_found(InputIterator first, InputIterator last, T const& value) {
		return first == last ? false
			: *first == value ? true
			: testspr::is_found(first + 1, last, value)
			;
	}
	template<typename InputRange, typename T>
	inline SPROUT_CONSTEXPR bool
	is_found(InputRange const& range, T const& value) {
		return testspr::is_found(sprout::begin(range), sprout::end(range), value);
	}

	//
	// count
	//
	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	count(InputIterator first, InputIterator last, T const& value) {
		return first == last ? 0
			: (*first == value ? 1 : 0) + testspr::count(first + 1, last, value)
			;
	}
	template<typename InputRange, typename T>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<typename InputRange::const_iterator>::difference_type
	count(InputRange const& range, T const& value) {
		return testspr::count(sprout::begin(range), sprout::end(range), value);
	}

	namespace detail {
		template<typename ForwardIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR bool
		is_permutation_impl(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			ForwardIterator1 first1_, ForwardIterator2 first2_
			)
		{
			return first1_ == last1 && first2_ == last2 ? true
				: testspr::count(first1, last1, *first1_) != testspr::count(first2, first2 + testspr::distance(first1, last1), *first1_)
					? false
				: testspr::detail::is_permutation_impl(first1, last1, first2, last2, first1_ + 1, first2_ + 1)
				;
		}
	}	// namespace detail
	//
	// is_permutation
	//
	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR bool
	is_permutation(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2
		)
	{
		return testspr::detail::is_permutation_impl(first1, last1, first2, last2, first1, first2);
	}
	template<typename ForwardRange1, typename ForwardRange2>
	inline SPROUT_CONSTEXPR bool
	is_permutation(ForwardRange1 const& range1, ForwardRange2 const& range2) {
		return testspr::is_permutation(
			sprout::begin(range1), sprout::end(range1),
			sprout::begin(range2), sprout::end(range2)
			);
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_ALGORITHM_HPP
