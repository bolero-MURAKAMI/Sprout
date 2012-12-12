#ifndef SPROUT_ALGORITHM_FIND_FIRST_OF_HPP
#define SPROUT_ALGORITHM_FIND_FIRST_OF_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/functional/bind2nd.hpp>
#include <sprout/algorithm/find_if.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		find_first_of_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, RandomAccessIterator1 found
			)
		{
			return found != first1 ? found
				: pivot == 0 ? sprout::find_if(first2, last2, sprout::bind2nd(pred, *first1)) != last2 ? first1 : last1
				: sprout::detail::find_first_of_impl_ra(
					sprout::next(first1, pivot), last1, first2, last2, pred,
					(NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) - pivot) / 2,
					sprout::detail::find_first_of_impl_ra(
						first1, sprout::next(first1, pivot), first2, last2, pred,
						pivot / 2,
						first1
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		find_first_of(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? last1
				: sprout::detail::find_first_of_impl_ra(
					first1, last1, first2, last2,
					pred, NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) / 2, first1
					)
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename InputIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR InputIterator1
		find_first_of_impl(
			InputIterator1 first1, InputIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred
			)
		{
			return first1 == last1 || sprout::find_if(first2, last2, sprout::bind2nd(pred, *first1)) != last2 ? first1
				: sprout::detail::find_first_of_impl(sprout::next(first1), last1, first2, last2, pred)
				;
		}
		template<typename InputIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR InputIterator1
		find_first_of(
			InputIterator1 first1, InputIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			void*
			)
		{
			return sprout::detail::find_first_of_impl(first1, last1, first2, last2, pred);
		}
	}	//namespace detail

	// 25.2.7 Find first
	//
	//	recursion depth:
	//		[first1, last1) is RandomAccessIterator -> O(log N1)
	//		otherwise -> O(N1)
	//		[first2, last2) is RandomAccessIterator -> O(log N2)
	//		otherwise -> O(N2)
	//
	template<typename InputIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR InputIterator1
	find_first_of(
		InputIterator1 first1, InputIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		BinaryPredicate pred
		)
	{
		typedef typename std::iterator_traits<InputIterator1>::iterator_category* category;
		return sprout::detail::find_first_of(first1, last1, first2, last2, pred, category());
	}

	template<typename InputIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR InputIterator1
	find_first_of(
		InputIterator1 first1, InputIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2
		)
	{
		return sprout::find_first_of(first1, last1, first2, last2, sprout::equal_to<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_FIRST_OF_HPP
