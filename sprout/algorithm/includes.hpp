#ifndef SPROUT_ALGORITHM_INCLUDES_HPP
#define SPROUT_ALGORITHM_INCLUDES_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/functional/less.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename Compare>
		inline SPROUT_CONSTEXPR RandomAccessIterator2
		includes_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, Compare comp,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot
			)
		{
			return first2 == last2 ? first2
				: pivot == 0 ? (!comp(*first1, *first2) && !comp(*first2, *first1) ? sprout::next(first2) : first2)
				: sprout::detail::includes_impl_ra(
					sprout::next(first1, pivot), last1,
					sprout::detail::includes_impl_ra(
						first1, sprout::next(first1, pivot),
						first2,
						last2, comp,
						pivot / 2
						),
					last2, comp,
					(sprout::distance(first1, last1) - pivot) / 2
					)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename Compare>
		inline SPROUT_CONSTEXPR bool
		includes(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, Compare comp,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? first2 == last2
				: sprout::detail::includes_impl_ra(
					first1, last1, first2, last2, comp,
					sprout::distance(first1, last1) / 2
					)
					== last2
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR bool
		includes_impl(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
			return first2 == last2 ? true
				: first1 == last1 ? false
				: !comp(*first1, *first2) && !comp(*first2, *first1)
					? sprout::detail::includes_impl(sprout::next(first1), last1, sprout::next(first2), last2)
				: sprout::detail::includes_impl(sprout::next(first1), last1, first2, last2)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR bool
		includes(
			InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp,
			void*
			)
		{
			return sprout::detail::includes_impl(first1, last1, first2, comp);
		}
	}	// namespace detail

	// 25.4.5.1 includes
	//
	//	recursion depth:
	//		[first, last) is RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
	//
	template<typename InputIterator1, typename InputIterator2, typename Compare>
	inline SPROUT_CONSTEXPR bool
	includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
		typedef typename std::iterator_traits<InputIterator1>::iterator_category* category;
		return sprout::detail::includes(first1, last1, first2, last2, comp, category());
	}

	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR bool
	includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		return sprout::includes(
			first1, last1, first2, last2,
			sprout::less<>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INCLUDES_HPP
