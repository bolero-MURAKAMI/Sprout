#ifndef SPROUT_ALGORITHM_IS_SORTED_UNTIL_HPP
#define SPROUT_ALGORITHM_IS_SORTED_UNTIL_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		is_sorted_until_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot, RandomAccessIterator found
			)
		{
			return found != first ? found
				: pivot == 0 ? (comp(*last, *first) ? first : last)
				: sprout::detail::is_sorted_until_impl_ra(
					sprout::next(first, pivot), last, comp,
					(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - pivot) / 2,
					sprout::detail::is_sorted_until_impl_ra(
						first, sprout::next(first, pivot), comp,
						pivot / 2,
						first
						)
					)
				;
		}
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		is_sorted_until(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			std::random_access_iterator_tag*
			)
		{
			return first == last || NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) == 1 ? last
				: sprout::next(
					sprout::detail::is_sorted_until_impl_ra(
						first, sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - 1), comp,
						(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - 1) / 2, first
						)
					)
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR ForwardIterator
		is_sorted_until_impl(ForwardIterator first, ForwardIterator next, ForwardIterator last, Compare comp) {
			return next == last ? last
				: comp(*next, *first) ? first
				: sprout::detail::is_sorted_until_impl(next, sprout::next(next), last, comp)
				;
		}
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR ForwardIterator
		is_sorted_until(
			ForwardIterator first, ForwardIterator last, Compare comp,
			void*
			)
		{
			return first == last ? last
				: sprout::detail::is_sorted_until_impl(first, sprout::next(first), last, comp)
				;
		}
	}	//namespace detail

	// 25.4.1.5 is_sorted
	template<typename ForwardIterator, typename Compare>
	inline SPROUT_CONSTEXPR ForwardIterator
	is_sorted_until(ForwardIterator first, ForwardIterator last, Compare comp) {
		typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
		return sprout::detail::is_sorted_until(first, last, comp, category());
	}

	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	is_sorted_until(ForwardIterator first, ForwardIterator last) {
		return sprout::is_sorted_until(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_SORTED_UNTIL_HPP
