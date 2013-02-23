#ifndef SPROUT_ALGORITHM_FIND_FIRST_OF_HPP
#define SPROUT_ALGORITHM_FIND_FIRST_OF_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/functional/bind2nd.hpp>
#include <sprout/algorithm/find_if.hpp>
#include <sprout/utility/pair/pair.hpp>

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
					(sprout::distance(first1, last1) - pivot) / 2,
					sprout::detail::find_first_of_impl_ra(
						first1, sprout::next(first1, pivot), first2, last2, pred,
						pivot / 2,
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
					pred, sprout::distance(first1, last1) / 2, first1
					)
				;
		}

		template<typename InputIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, bool>
		find_first_of_impl_1(
			sprout::pair<InputIterator1, bool> current,
			InputIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator1, bool> type;
			return current.second || current.first == last1 ? current
				: n == 1 ? sprout::find_if(first2, last2, sprout::bind2nd(pred, *current.first)) != last2
					? type(current.first, true)
					: type(sprout::next(current.first), false)
				: sprout::detail::find_first_of_impl_1(
					sprout::detail::find_first_of_impl_1(
						current,
						last1, first2, last2, pred, n / 2
						),
					last1, first2, last2, pred, n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, bool>
		find_first_of_impl(
			sprout::pair<InputIterator1, bool> current,
			InputIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator1, bool> type;
			return current.second || current.first == last1 ? current
				: sprout::detail::find_first_of_impl(
					sprout::detail::find_first_of_impl_1(
						current,
						last1, first2, last2, pred, n
						),
					last1, first2, last2, pred, n * 2
					)
				;
		}
		template<typename InputIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR InputIterator1
		find_first_of(
			InputIterator1 first1, InputIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			std::input_iterator_tag*
			)
		{
			typedef sprout::pair<InputIterator1, bool> type;
			return sprout::detail::find_first_of_impl(type(first1, false), last1, first2, last2, pred, 1).first;
		}
	}	// namespace detail

	// 25.2.7 Find first
	//
	//	recursion depth:
	//		O(log(N1+N2))
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
