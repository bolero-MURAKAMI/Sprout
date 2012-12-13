#ifndef SPROUT_ALGORITHM_SEARCH_HPP
#define SPROUT_ALGORITHM_SEARCH_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/detail/algorithm/search_one.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		search_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, RandomAccessIterator1 last1_, RandomAccessIterator1 searched
			)
		{
			return searched < first1 || searched == last1_ ? searched
				: pivot == 0 ? sprout::detail::search_one(first1, last1_, first2, last2, pred)
				: sprout::detail::search_impl_ra(
					sprout::next(first1, pivot), last1, first2, last2, pred,
					(NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) - pivot) / 2, last1_,
					sprout::detail::search_impl_ra(
						first1, sprout::next(first1, pivot), first2, last2, pred,
						pivot / 2, last1_,
						first1
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		search(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? last1
				: sprout::detail::search_impl_ra(
					first1, last1, first2, last2, pred,
					NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) / 2, last1, first1
					)
				;
		}

		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		search_impl(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			ForwardIterator1 searched
			)
		{
			return searched == first1 || searched == last1 ? searched
				: sprout::detail::search_impl(
					sprout::next(first1), last1, first2, last2, pred,
					sprout::detail::search_one(sprout::next(first1), last1, first2, last2, pred)
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		search(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			void*
			)
		{
			return sprout::detail::search_impl(
				first1, last1, first2, last2, pred,
				sprout::detail::search_one(first1, last1, first2, last2, pred)
				);
		}
	}	//namespace detail

	// 25.2.13 Search
	//
	//	recursion depth:
	//		[first1, last1) is RandomAccessIterator -> O(log N1)
	//		otherwise -> O(N1)
	//		[first2, last2) is RandomAccessIterator -> O(log N2)
	//		otherwise -> O(N2)
	//
	template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator1
	search(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		BinaryPredicate pred
		)
	{
		typedef typename std::iterator_traits<ForwardIterator1>::iterator_category* category;
		return sprout::detail::search(first1, last1, first2, last2, pred, category());
	}

	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR ForwardIterator1
	search(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2
		)
	{
		return sprout::search(first1, last1, first2, last2, sprout::equal_to<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_SEARCH_HPP
