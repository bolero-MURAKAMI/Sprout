#ifndef SPROUT_ALGORITHM_MAX_ELEMENT_HPP
#define SPROUT_ALGORITHM_MAX_ELEMENT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename InputIterator, typename Compare>
		inline SPROUT_CONSTEXPR InputIterator
		iter_max(InputIterator a, InputIterator b, Compare comp) {
			return comp(*a, *b) ? b : a;
		}

		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		max_element_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? first
				: sprout::detail::iter_max(
					sprout::detail::max_element_impl_ra(
						first, sprout::next(first, pivot), comp,
						pivot / 2
						),
					sprout::detail::max_element_impl_ra(
						sprout::next(first, pivot), last, comp,
						(sprout::distance(first, last) - pivot) / 2
						),
					comp
					)
				;
		}
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		max_element(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? last
				: sprout::detail::max_element_impl_ra(
					first, last, comp,
					sprout::distance(first, last) / 2
					)
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR ForwardIterator
		max_element_impl(
			ForwardIterator first, ForwardIterator last, Compare comp,
			ForwardIterator found
			)
		{
			return first == last ? found
				: sprout::detail::max_element_impl(sprout::next(first), last, comp, sprout::detail::iter_max(found, first, comp))
				;
		}
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR ForwardIterator
		max_element(
			ForwardIterator first, ForwardIterator last, Compare comp,
			void*
			)
		{
			return first == last ? last
				: sprout::detail::max_element_impl(sprout::next(first), last, comp, first)
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
	inline SPROUT_CONSTEXPR ForwardIterator
	max_element(ForwardIterator first, ForwardIterator last, Compare comp) {
		typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
		return sprout::detail::max_element(first, last, comp, category());
	}

	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	max_element(ForwardIterator first, ForwardIterator last) {
		return sprout::max_element(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MAX_ELEMENT_HPP
