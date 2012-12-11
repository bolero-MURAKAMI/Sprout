#ifndef SPROUT_ALGORITHM_IS_PERMUTATION_HPP
#define SPROUT_ALGORITHM_IS_PERMUTATION_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/functional/bind2nd.hpp>
#include <sprout/algorithm/count_if.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			RandomAccessIterator2 first2, RandomAccessIterator2 last2,
			BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot
			)
		{
			return pivot == 0 ? sprout::count_if(first1, last1, sprout::bind2nd(pred, *first1))
					<= sprout::count_if(first2, last2, sprout::bind2nd(pred, *first1))
				: sprout::detail::is_permutation_impl_ra(
					first1, last1, first2, last2,
					pred, pivot / 2
					)
					&& sprout::detail::is_permutation_impl_ra(
						sprout::next(first1, pivot), last1, first2, last2,
						pred, (NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? true
				: sprout::detail::is_permutation_impl_ra(
					first1, last1, first2, sprout::next(first2, NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1)),
					pred, NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) / 2
					)
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation_impl(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred
			)
		{
			return first1 == last1 ? true
				: sprout::count_if(first1, last1, sprout::bind2nd(pred, *first1))
					<= sprout::count_if(first2, last2, sprout::bind2nd(pred, *first1))
					&& sprout::detail::is_permutation_impl(sprout::next(first1), last1, first2, last2, pred)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation(
			ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate pred,
			void*
			)
		{
			return sprout::detail::is_permutation_impl(
				first1, last1, first2, sprout::next(first2, NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1)), pred
				);
		}
	}	// namespace detail

	// 25.2.12 Is permutation
	template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR bool
	is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate pred) {
		typedef typename sprout::common_iterator_category<ForwardIterator1, ForwardIterator2>::type* category;
		return sprout::detail::is_permutation(first1, last1, first2, pred, category());
	}

	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR bool
	is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2) {
		return sprout::is_permutation(first1, last1, first2, sprout::equal_to<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_PERMUTATION_HPP
