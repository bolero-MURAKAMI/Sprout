#ifndef SPROUT_ALGORITHM_ADJACENT_FIND_HPP
#define SPROUT_ALGORITHM_ADJACENT_FIND_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		adjacent_find_impl_ra_1(RandomAccessIterator found, RandomAccessIterator last) {
			return NS_SSCRISK_CEL_OR_SPROUT::distance(found, last) == 1 ? last
				: found
				;
		}
		template<typename RandomAccessIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		adjacent_find_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot, RandomAccessIterator found
			)
		{
			return found != first ? found
				: pivot == 0 ? (pred(*first, *last) ? first : last)
				: sprout::detail::adjacent_find_impl_ra(
					sprout::next(first, pivot), last, pred,
					(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - pivot) / 2,
					sprout::detail::adjacent_find_impl_ra(
						first, sprout::next(first, pivot), pred,
						pivot / 2,
						first
						)
					)
				;
		}
		template<typename RandomAccessIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		adjacent_find(
			RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first == last || NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) == 1 ? last
				: adjacent_find_impl_ra_1(
					sprout::detail::adjacent_find_impl_ra(
						first, sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - 1), pred,
						(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - 1) / 2, first
						),
					last
					)
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename ForwardIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator
		adjacent_find_impl(ForwardIterator first, ForwardIterator next, ForwardIterator last, BinaryPredicate pred) {
			return next == last ? last
				: pred(*first, *next) ? first
				: sprout::detail::adjacent_find_impl(next, sprout::next(next), last, pred)
				;
		}
		template<typename ForwardIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator
		adjacent_find(
			ForwardIterator first, ForwardIterator last, BinaryPredicate pred,
			void*
			)
		{
			return first == last ? last
				: sprout::detail::adjacent_find_impl(first, sprout::next(first), last, pred)
				;
		}
	}	//namespace detail

	// 25.2.8 Adjacent find
	//
	//	recursion depth:
	//		[first, last) is RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
	//
	template<typename ForwardIterator, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator
	adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred) {
		typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
		return sprout::detail::adjacent_find(first, last, pred, category());
	}

	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	adjacent_find(ForwardIterator first, ForwardIterator last) {
		return sprout::adjacent_find(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::equal_to<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_ADJACENT_FIND_HPP
