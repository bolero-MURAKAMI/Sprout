#ifndef SPROUT_ALGORITHM_FIND_END_HPP
#define SPROUT_ALGORITHM_FIND_END_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/search.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/detail/algorithm/search_one.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		find_end_impl_ra_1(RandomAccessIterator1 first1, RandomAccessIterator1 result, RandomAccessIterator1 searched) {
			return searched == first1 ? searched
				: result
				;
		}
		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		find_end_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, RandomAccessIterator1 last1_, RandomAccessIterator1 result,
			RandomAccessIterator1 searched
			)
		{
			return searched == last1_ ? result
				: searched < first1 ? pivot == 0
					? sprout::detail::find_end_impl_ra_1(
						first1, searched,
						sprout::detail::search_one(first1, last1_, first2, last2, pred)
						)
					: sprout::detail::find_end_impl_ra(
						sprout::next(first1, pivot), last1, first2, last2, pred,
						(NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) - pivot) / 2, last1_, searched,
						sprout::detail::find_end_impl_ra(
							first1, sprout::next(first1, pivot), first2, last2, pred,
							pivot / 2, last1_, searched,
							first1
							)
						)
				: pivot == 0 ? sprout::detail::search_one(first1, last1_, first2, last2, pred)
				: sprout::detail::find_end_impl_ra(
					sprout::next(first1, pivot), last1, first2, last2, pred,
					(NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) - pivot) / 2, last1_, result,
					sprout::detail::find_end_impl_ra(
						first1, sprout::next(first1, pivot), first2, last2, pred,
						pivot / 2, last1_, result,
						first1
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		find_end(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? last1
				: sprout::detail::find_end_impl_ra(
					first1, last1, first2, last2, pred,
					NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) / 2, last1, last1,
					first1
					)
				;
		}

		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		find_end_impl(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			ForwardIterator1 result
			)
		{
			return first1 == last1 ? result
				: sprout::detail::find_end_impl(
					sprout::search(sprout::next(first1), last1, first2, last2, pred), last1, first2, last2, pred,
					first1
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		find_end(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			void*
			)
		{
			return first2 == last2 ? last1
				: sprout::detail::find_end_impl(
					sprout::search(first1, last1, first2, last2, pred), last1, first2, last2, pred,
					last1
					)
				;
		}
	}	// namespace detail

	// 25.2.6 Find end
	template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator1
	find_end(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		BinaryPredicate pred
		)
	{
		typedef typename std::iterator_traits<ForwardIterator1>::iterator_category* category;
		return sprout::detail::find_end(first1, last1, first2, last2, pred, category());
	}

	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR ForwardIterator1
	find_end(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2
		)
	{
		return sprout::find_end(first1, last1, first2, last2, sprout::equal_to<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_END_HPP
