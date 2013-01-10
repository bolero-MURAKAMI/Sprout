#ifndef SPROUT_ALGORITHM_IS_SORTED_HPP
#define SPROUT_ALGORITHM_IS_SORTED_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>
#include <sprout/algorithm/is_sorted_until.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR bool
		is_sorted_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? !comp(*last, *first)
				: sprout::detail::is_sorted_impl_ra(
					first, sprout::next(first, pivot), comp,
					pivot / 2
					)
					&& sprout::detail::is_sorted_impl_ra(
						sprout::next(first, pivot), last, comp,
						(sprout::distance(first, last) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			bool
		>::type
		is_sorted(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			std::random_access_iterator_tag*
			)
		{
			return first == last || sprout::distance(first, last) == 1 ? true
				: sprout::detail::is_sorted_impl_ra(
					first, sprout::next(first, sprout::distance(first, last) - 1), comp,
					(sprout::distance(first, last) - 1) / 2
					)
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR bool
		is_sorted(
			ForwardIterator first, ForwardIterator last, Compare comp,
			void*
			)
		{
			return sprout::is_sorted_until(first, last, comp) == last;
		}
	}	// namespace detail

	// 25.4.1.5 is_sorted
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator, typename Compare>
	inline SPROUT_CONSTEXPR bool
	is_sorted(ForwardIterator first, ForwardIterator last, Compare comp) {
		typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
		return sprout::detail::is_sorted(first, last, comp, category());
	}

	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR bool
	is_sorted(ForwardIterator first, ForwardIterator last) {
		return sprout::is_sorted(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_SORTED_HPP
