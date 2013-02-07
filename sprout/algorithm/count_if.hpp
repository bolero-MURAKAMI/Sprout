#ifndef SPROUT_ALGORITHM_COUNT_IF_HPP
#define SPROUT_ALGORITHM_COUNT_IF_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<RandomAccessIterator>::difference_type
		count_if_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, Predicate pred,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? (pred(*first) ? 1 : 0)
				: sprout::detail::count_if_impl_ra(
					first, sprout::next(first, pivot), pred,
					pivot / 2
					)
					+ sprout::detail::count_if_impl_ra(
						sprout::next(first, pivot), last, pred,
						(sprout::distance(first, last) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type
		>::type
		count_if(
			RandomAccessIterator first, RandomAccessIterator last, Predicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? 0
				: sprout::detail::count_if_impl_ra(first, last, pred, sprout::distance(first, last) / 2)
				;
		}

		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type>
		count_if_impl_1(
			sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> const& current,
			InputIterator last, Predicate pred, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return current.first == last ? current
				: n == 1 ? type(sprout::next(current.first), current.second + (pred(*current.first) ? 1 : 0))
				: sprout::detail::count_if_impl_1(
					sprout::detail::count_if_impl_1(
						current,
						last, pred, n / 2
						),
					last, pred, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type>
		count_if_impl(
			sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> const& current,
			InputIterator last, Predicate pred, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return current.first == last ? current
				: sprout::detail::count_if_impl(
					sprout::detail::count_if_impl_1(
						current,
						last, pred, n
						),
					last, pred, n * 2
					)
				;
		}
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_if(
			InputIterator first, InputIterator last, Predicate pred,
			void*
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return sprout::detail::count_if_impl(type(first, 0), last, pred, 1).second;
		}
	}	// namespace detail

	// 25.2.9 Count
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator, typename Predicate>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	count_if(InputIterator first, InputIterator last, Predicate pred) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::count_if(first, last, pred, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_COUNT_IF_HPP
