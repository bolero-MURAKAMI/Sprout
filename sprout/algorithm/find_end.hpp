#ifndef SPROUT_ALGORITHM_FIND_END_HPP
#define SPROUT_ALGORITHM_FIND_END_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/utility/pair.hpp>
#include <sprout/detail/algorithm/search_one.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		find_end_impl_check_ra(RandomAccessIterator1 first1, RandomAccessIterator1 result, RandomAccessIterator1 searched) {
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
					? sprout::detail::find_end_impl_check_ra(
						first1, searched,
						sprout::detail::search_one(first1, last1_, first2, last2, pred)
						)
					: sprout::detail::find_end_impl_ra(
						sprout::next(first1, pivot), last1, first2, last2, pred,
						(sprout::distance(first1, last1) - pivot) / 2, last1_, searched,
						sprout::detail::find_end_impl_ra(
							first1, sprout::next(first1, pivot), first2, last2, pred,
							pivot / 2, last1_, searched,
							first1
							)
						)
				: pivot == 0 ? sprout::detail::search_one(first1, last1_, first2, last2, pred)
				: sprout::detail::find_end_impl_ra(
					sprout::next(first1, pivot), last1, first2, last2, pred,
					(sprout::distance(first1, last1) - pivot) / 2, last1_, result,
					sprout::detail::find_end_impl_ra(
						first1, sprout::next(first1, pivot), first2, last2, pred,
						pivot / 2, last1_, result,
						first1
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value,
			RandomAccessIterator1
		>::type
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
					sprout::distance(first1, last1) / 2, last1, last1,
					first1
					)
				;
		}

		template<typename ForwardIterator1>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, ForwardIterator1>
		find_end_impl_check(sprout::pair<ForwardIterator1, ForwardIterator1> const& current, ForwardIterator1 last1, ForwardIterator1 searched) {
			typedef sprout::pair<ForwardIterator1, ForwardIterator1> type;
			return searched == current.first ? type(sprout::next(current.first), searched)
				: searched == last1 ? type(last1, current.second)
				: type(sprout::next(current.first), current.second)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, ForwardIterator1>
		find_end_impl_1(
			sprout::pair<ForwardIterator1, ForwardIterator1> const& current,
			ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			typedef sprout::pair<ForwardIterator1, ForwardIterator1> type;
			return current.first == last1 ? current
				: n == 1 ? sprout::detail::find_end_impl_check(
					current, last1,
					sprout::detail::search_one(current.first, last1, first2, last2, pred)
					)
				: sprout::detail::find_end_impl_1(
					sprout::detail::find_end_impl_1(
						current,
						last1, first2, last2, pred, n / 2
						),
					last1, first2, last2, pred, n - n / 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, ForwardIterator1>
		find_end_impl(
			sprout::pair<ForwardIterator1, ForwardIterator1> const& current,
			ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			typedef sprout::pair<ForwardIterator1, ForwardIterator1> type;
			return current.first == last1 ? current
				: sprout::detail::find_end_impl(
					sprout::detail::find_end_impl_1(
						current,
						last1, first2, last2, pred, n
						),
					last1, first2, last2, pred, n * 2
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
			typedef sprout::pair<ForwardIterator1, ForwardIterator1> type;
			return sprout::detail::find_end_impl(type(first1, last1), last1, first2, last2, pred, 1).second;
		}
	}	// namespace detail

	// 25.2.6 Find end
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
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
