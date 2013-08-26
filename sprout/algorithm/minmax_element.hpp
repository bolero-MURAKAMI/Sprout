/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_MINMAX_ELEMENT_HPP
#define SPROUT_ALGORITHM_MINMAX_ELEMENT_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/utility/pair/access.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename ForwardIteratorPair, typename Compare>
		inline SPROUT_CONSTEXPR ForwardIteratorPair
		iter_minmax_pair(ForwardIteratorPair const& a, ForwardIteratorPair const& b, Compare comp) {
			return ForwardIteratorPair(
				comp(*sprout::first(b), *sprout::first(a)) ? sprout::first(b) : sprout::first(a),
				comp(*sprout::second(b), *sprout::second(a)) ? sprout::second(a) : sprout::second(b)
				);
		}
		template<typename ForwardIteratorPair, typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR ForwardIteratorPair
		iter_minmax(ForwardIteratorPair const& a, ForwardIterator b, Compare comp) {
			return ForwardIteratorPair(
				comp(*b, *sprout::first(a)) ? b : sprout::first(a),
				comp(*sprout::second(b), *a) ? a : sprout::second(b)
				);
		}

		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<RandomAccessIterator, RandomAccessIterator>
		minmax_element_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? sprout::pair<RandomAccessIterator, RandomAccessIterator>(first, first)
				: sprout::detail::iter_minmax_pair(
					sprout::detail::minmax_element_impl_ra(
						first, sprout::next(first, pivot), comp,
						pivot / 2
						),
					sprout::detail::minmax_element_impl_ra(
						sprout::next(first, pivot), last, comp,
						(sprout::distance(first, last) - pivot) / 2
						),
					comp
					)
				;
		}
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			sprout::pair<RandomAccessIterator, RandomAccessIterator>
		>::type
		minmax_element(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? sprout::pair<RandomAccessIterator, RandomAccessIterator>(last, last)
				: sprout::detail::minmax_element_impl_ra(
					first, last, comp,
					sprout::distance(first, last) / 2
					)
				;
		}

		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, sprout::pair<ForwardIterator, ForwardIterator> >
		minmax_element_impl_1(
			sprout::pair<ForwardIterator, sprout::pair<ForwardIterator, ForwardIterator> > const& current,
			ForwardIterator last, Compare comp, typename std::iterator_traits<ForwardIterator>::difference_type n
			)
		{
			typedef sprout::pair<ForwardIterator, sprout::pair<ForwardIterator, ForwardIterator> > type;
			return current.first == last ? current
				: n == 1 ? type(sprout::next(current.first), sprout::detail::iter_minmax(current.second, current.first, comp))
				: sprout::detail::minmax_element_impl_1(
					sprout::detail::minmax_element_impl_1(
						current,
						last, comp, n / 2
						),
					last, comp, n - n / 2
					)
				;
		}
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, sprout::pair<ForwardIterator, ForwardIterator> >
		minmax_element_impl(
			sprout::pair<ForwardIterator, sprout::pair<ForwardIterator, ForwardIterator> > const& current,
			ForwardIterator last, Compare comp, typename std::iterator_traits<ForwardIterator>::difference_type n
			)
		{
			return current.first == last ? current
				: sprout::detail::minmax_element_impl(
					sprout::detail::minmax_element_impl_1(
						current,
						last, comp, n
						),
					last, comp, n * 2
					)
				;
		}
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		minmax_element(
			ForwardIterator first, ForwardIterator last, Compare comp,
			std::forward_iterator_tag*
			)
		{
			typedef sprout::pair<ForwardIterator, sprout::pair<ForwardIterator, ForwardIterator> > type;
			return first == last ? sprout::pair<ForwardIterator, ForwardIterator>(first, first)
				: sprout::detail::minmax_element_impl(type(sprout::next(first), sprout::pair<ForwardIterator, ForwardIterator>(first, first)), last, comp, 1).second
				;
		}
	}	// namespace detail

	// 25.4.7 Minimum and maximum
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator, typename Compare>
	inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
	minmax_element(ForwardIterator first, ForwardIterator last, Compare comp) {
		typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
		return sprout::detail::minmax_element(first, last, comp, category());
	}

	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
	minmax_element(ForwardIterator first, ForwardIterator last) {
		return sprout::minmax_element(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MINMAX_ELEMENT_HPP
