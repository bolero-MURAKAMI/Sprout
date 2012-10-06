#ifndef SPROUT_ALGORITHM_IS_PERMUTATION_HPP
#define SPROUT_ALGORITHM_IS_PERMUTATION_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/count.hpp>
#include <sprout/algorithm/count_if.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		template<typename ForwardIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR bool
		is_permutation_impl(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator1 first1_
			)
		{
			return first1_ == last1 ? true
				: sprout::count(first1, last1, *first1_)
					== sprout::count(first2, sprout::next(first2, NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1)), *first1_)
					&& sprout::detail::is_permutation_impl(first1, last1, first2, sprout::next(first1_))
					? true
				: false
				;
		}

		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation_impl(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator1 first1_,
			BinaryPredicate pred
			)
		{
			return first1_ == last1 ? true
				: sprout::count_if(first1, last1, NS_SSCRISK_CEL_OR_SPROUT::bind2nd(pred, *first1_))
					== sprout::count_if(
						first2, sprout::next(first2, NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1)),
						NS_SSCRISK_CEL_OR_SPROUT::bind2nd(pred, *first1_)
						)
					&& sprout::detail::is_permutation_impl(first1, last1, first2, sprout::next(first1_), pred)
					? true
				: false
				;
		}
	}	// namespace detail

	// 25.2.12 Is permutation
	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR bool
	is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2) {
		return sprout::detail::is_permutation_impl(first1, last1, first2, first1);
	}

	template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR bool
	is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate pred) {
		return sprout::detail::is_permutation_impl(first1, last1, first2, first1, pred);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_PERMUTATION_HPP
