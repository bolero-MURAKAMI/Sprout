#ifndef SPROUT_ALGORITHM_ALL_OF_HPP
#define SPROUT_ALGORITHM_ALL_OF_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>
#include <sprout/utility/pair.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Predicate>
		inline SPROUT_CONSTEXPR bool
		all_of_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, Predicate pred,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? pred(*first)
				: sprout::detail::all_of_impl_ra(
					first, sprout::next(first, pivot), pred,
					pivot / 2
					)
					&& sprout::detail::all_of_impl_ra(
						sprout::next(first, pivot), last, pred,
						(sprout::distance(first, last) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			bool
		>::type
		all_of(
			RandomAccessIterator first, RandomAccessIterator last, Predicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? true
				: sprout::detail::all_of_impl_ra(first, last, pred, sprout::distance(first, last) / 2)
				;
		}

		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, bool>
		all_of_impl_1(
			sprout::pair<InputIterator, bool> const& current,
			InputIterator last, Predicate pred, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, bool> type;
			return !current.second || current.first == last ? current
				: n == 1 ? pred(*current.first) ? type(sprout::next(current.first), true) : type(current.first, false)
				: sprout::detail::all_of_impl_1(
					sprout::detail::all_of_impl_1(
						current,
						last, pred, n / 2
						),
					last, pred, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, bool>
		all_of_impl(
			sprout::pair<InputIterator, bool> const& current,
			InputIterator last, Predicate pred, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, bool> type;
			return !current.second || current.first == last ? current
				: sprout::detail::all_of_impl(
					sprout::detail::all_of_impl_1(
						current,
						last, pred, n
						),
					last, pred, n * 2
					)
				;
		}
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR bool
		all_of(
			InputIterator first, InputIterator last, Predicate pred,
			void*
			)
		{
			typedef sprout::pair<InputIterator, bool> type;
			return sprout::detail::all_of_impl(type(first, true), last, pred, 1).second;
		}
	}	// namespace detail

	// 25.2.1 All of
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator, typename Predicate>
	inline SPROUT_CONSTEXPR bool
	all_of(InputIterator first, InputIterator last, Predicate pred) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::all_of(first, last, pred, category());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_ALL_OF_HPP
