#ifndef SPROUT_DETAIL_ALGORITHM_SEARCH_ONE_HPP
#define SPROUT_DETAIL_ALGORITHM_SEARCH_ONE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/algorithm/mismatch.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		search_one_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred
			)
		{
			return sprout::detail::mismatch_impl_ra(
					first1, last1, first2, pred,
					NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) / 2, first1
					)
					== last1
				? first1
				: last1
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		search_one(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) < NS_SSCRISK_CEL_OR_SPROUT::distance(first2, last2) ? last1
				: first1 == last1 ? first1
				: sprout::detail::search_one_impl_ra(
					first1, sprout::next(first1, NS_SSCRISK_CEL_OR_SPROUT::distance(first2, last2)), first2, last2, pred
					)
				;
		}

		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		search_one_impl(
			ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			ForwardIterator1 first1_
			)
		{
			return first2 == last2 ? first1_
				: first1 == last1 ? last1
				: !pred(*first1, *first2) ? first1
				: sprout::detail::search_one_impl(sprout::next(first1), last1, sprout::next(first2), last2, pred, first1_)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		search_one(
			ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			void*
			)
		{
			return sprout::detail::search_one_impl(first1, last1, first2, last2, pred, first1);
		}

		//
		// search_one
		//
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		search_one(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred) {
			typedef typename sprout::common_iterator_category<ForwardIterator1, ForwardIterator2>::type* category;
			return sprout::detail::search_one(first1, last1, first2, last2, pred, category());
		}
		template<typename ForwardIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR ForwardIterator1
		search_one(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2) {
			return sprout::detail::search_one(first1, last1, first2, last2, sprout::equal_to<>());
		}
	}	//namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_SEARCH_ONE_HPP
