#ifndef SPROUT_ALGORITHM_MISMATCH_HPP
#define SPROUT_ALGORITHM_MISMATCH_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/utility/pair.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/functional/equal_to.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2>
		inline SPROUT_CONSTEXPR sprout::pair<RandomAccessIterator1, RandomAccessIterator2>
		mismatch_impl_ra_1(RandomAccessIterator1 first1, RandomAccessIterator2 first2, RandomAccessIterator1 found) {
			return sprout::pair<RandomAccessIterator1, RandomAccessIterator2>{
				found, sprout::next(first2, NS_SSCRISK_CEL_OR_SPROUT::distance(first1, found))
				};
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		mismatch_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, RandomAccessIterator1 found
			)
		{
			return found != first1 ? found
				: pivot == 0 ? (!pred(*first1, *first2) ? first1 : last1)
				: sprout::detail::mismatch_impl_ra(
					sprout::next(first1, pivot), last1, sprout::next(first2, pivot), pred,
					(NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) - pivot) / 2,
					sprout::detail::mismatch_impl_ra(
						first1, sprout::next(first1, pivot), first2, pred,
						pivot / 2,
						first1
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<RandomAccessIterator1, RandomAccessIterator2>
		mismatch(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? sprout::pair<RandomAccessIterator1, RandomAccessIterator2>{first1, first2}
				: sprout::detail::mismatch_impl_ra_1(
					first1, first2,
					sprout::detail::mismatch_impl_ra(
						first1, last1, first2, pred,
						NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) / 2, first1
						)
					)
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		mismatch_impl(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
			return first1 == last1 || !pred(*first1, *first2)
				? sprout::pair<InputIterator1, InputIterator2>{first1, first2}
				: sprout::detail::mismatch_impl(sprout::next(first1), last1, sprout::next(first2))
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		mismatch(
			InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred,
			void*
			)
		{
			return sprout::detail::mismatch_impl(first1, last1, first2, pred);
		}
	}	//namespace detail

	// 25.2.10 Mismatch
	//
	//	recursion depth:
	//		[first1, last1), first2 are RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
	//
	template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		typedef typename sprout::common_iterator_category<InputIterator1, InputIterator2>::type* category;
		return sprout::detail::mismatch(first1, last1, first2, pred, category());
	}
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
	mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		return sprout::mismatch(first1, last1, first2, sprout::equal_to<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MISMATCH_HPP
