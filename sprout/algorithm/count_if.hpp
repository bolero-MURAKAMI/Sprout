#ifndef SPROUT_ALGORITHM_COUNT_IF_HPP
#define SPROUT_ALGORITHM_COUNT_IF_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<RandomAccessIterator>::difference_type
		count_if_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, Predicate pred,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? (pred(*first) ? 1 : 0)
				: sprout::detail::count_if_impl_ra(
					first, sprout::next(first, pivot), pred,
					pivot / 2
					)
					+ sprout::detail::count_if_impl_ra(
						sprout::next(first, pivot), last, pred,
						(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<RandomAccessIterator>::difference_type
		count_if(
			RandomAccessIterator first, RandomAccessIterator last, Predicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? 0
				: sprout::detail::count_if_impl_ra(first, last, pred, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2)
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_if_impl(InputIterator first, InputIterator last, Predicate pred) {
			return first == last ? 0
				: (pred(*first) ? 1 : 0) + sprout::detail::count_if_impl(sprout::next(first), last, pred)
				;
		}
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_if(
			InputIterator first, InputIterator last, Predicate pred,
			void*
			)
		{
			return sprout::detail::count_if_impl(first, last, pred);
		}
	}	//namespace detail

	// 25.2.9 Count
	//
	//	recursion depth:
	//		[first, last) is RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
	//
	template<typename InputIterator, typename Predicate>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	count_if(InputIterator first, InputIterator last, Predicate pred) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::count_if(first, last, pred, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_COUNT_IF_HPP
