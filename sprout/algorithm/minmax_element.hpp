#ifndef SPROUT_ALGORITHM_MINMAX_ELEMENT_HPP
#define SPROUT_ALGORITHM_MINMAX_ELEMENT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/pair.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename InputIteratorPair, typename Compare>
		inline SPROUT_CONSTEXPR InputIteratorPair
		iter_minmax(InputIteratorPair a, InputIteratorPair b, Compare comp) {
			return InputIteratorPair(
				comp(*sprout::first(b), *sprout::first(a)) ? sprout::first(b) : sprout::first(a),
				comp(*sprout::second(a), *sprout::second(b)) ? sprout::second(b) : sprout::second(a)
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
				: sprout::detail::iter_minmax(
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
		inline SPROUT_CONSTEXPR sprout::pair<RandomAccessIterator, RandomAccessIterator>
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

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		minmax_element_impl(
			ForwardIterator first, ForwardIterator last, Compare comp,
			ForwardIterator min, ForwardIterator max
			)
		{
			return first == last ? sprout::pair<ForwardIterator, ForwardIterator>(min, max)
				: comp(*first, *min) ? sprout::detail::minmax_element_impl(sprout::next(first), last, comp, first, max)
				: sprout::detail::minmax_element_impl(sprout::next(first), last, comp, min, comp(*first, *max) ? max : first)
				;
		}
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		minmax_element(
			ForwardIterator first, ForwardIterator last, Compare comp,
			void*
			)
		{
			return first == last ? sprout::pair<ForwardIterator, ForwardIterator>(last, last)
				: sprout::detail::minmax_element_impl(sprout::next(first), last, comp, first, first)
				;
		}
	}	// namespace detail

	// 25.4.7 Minimum and maximum
	//
	//	recursion depth:
	//		[first, last) is RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
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
