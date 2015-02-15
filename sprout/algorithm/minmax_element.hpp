/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
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
				comp(*b, *sprout::second(a)) ? sprout::second(a) : b
				);
		}
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		iter_minmax(ForwardIterator a, ForwardIterator b, Compare comp) {
			typedef sprout::pair<ForwardIterator, ForwardIterator> type;
			return comp(*b, *a)
				? type(b, a)
				: type(a, b)
				;
		}

		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<RandomAccessIterator, RandomAccessIterator>
		minmax_element_impl_ra(
			RandomAccessIterator first, Compare comp,
			typename std::iterator_traits<RandomAccessIterator>::difference_type half
			)
		{
			return half == 1
				? iter_minmax(first, sprout::next(first), comp)
				: sprout::detail::iter_minmax_pair(
					sprout::detail::minmax_element_impl_ra(
						first, comp, half / 2
						),
					sprout::detail::minmax_element_impl_ra(
						sprout::next(first, half - (half & 1)), comp, (half + 1) / 2
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
			return first == last || sprout::next(first) == last
				? sprout::pair<RandomAccessIterator, RandomAccessIterator>(first, first)
				: sprout::distance(first, last) % 2 == 0
					? sprout::detail::minmax_element_impl_ra(
						first, comp,
						sprout::distance(first, last) / 2
						)
					: sprout::detail::iter_minmax(
						sprout::detail::minmax_element_impl_ra(
							first, comp,
							sprout::distance(first, last) / 2
							),
						sprout::prev(last),
						comp
						)
				;
		}

		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, sprout::pair<ForwardIterator, ForwardIterator> >
		minmax_element_impl_3(
			sprout::pair<ForwardIterator, ForwardIterator> minmax,
			ForwardIterator first, ForwardIterator next,
			ForwardIterator last, Compare comp) {
			typedef sprout::pair<ForwardIterator, sprout::pair<ForwardIterator, ForwardIterator> > type;
			return next == last
				? type(
					next,
					sprout::detail::iter_minmax(minmax, first, comp)
					)
				: type(
					sprout::next(next),
					sprout::detail::iter_minmax_pair(
						minmax,
						sprout::detail::iter_minmax(first, next, comp),
						comp
						)
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
			return current.first == last ? current
				: n == 1 ? sprout::detail::minmax_element_impl_3(
						current.second, current.first, sprout::next(current.first),
						last, comp)
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
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, sprout::pair<ForwardIterator, ForwardIterator> >
		minmax_element_impl_2(
			ForwardIterator first, ForwardIterator next, ForwardIterator last, Compare comp
			)
		{
			typedef sprout::pair<ForwardIterator, ForwardIterator> type;
			return next == last ? sprout::pair<ForwardIterator, type>(next, type(first, first))
				: sprout::pair<ForwardIterator, type>(sprout::next(next), iter_minmax(first, next, comp))
				;
		}

		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		minmax_element(
			ForwardIterator first, ForwardIterator last, Compare comp,
			std::forward_iterator_tag*
			)
		{
			return first == last ? sprout::pair<ForwardIterator, ForwardIterator>(first, first)
				: sprout::detail::minmax_element_impl(
					sprout::detail::minmax_element_impl_2(first, sprout::next(first), last, comp),
					last, comp, 1).second
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
