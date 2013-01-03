#ifndef SPROUT_ALGORITHM_ADJACENT_FIND_HPP
#define SPROUT_ALGORITHM_ADJACENT_FIND_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>
#include <sprout/tuple/tuple.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		adjacent_find_impl_check_ra(RandomAccessIterator found, RandomAccessIterator last) {
			return sprout::distance(found, last) == 1 ? last
				: found
				;
		}
		template<typename RandomAccessIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR RandomAccessIterator
		adjacent_find_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot, RandomAccessIterator found
			)
		{
			return found != first ? found
				: pivot == 0 ? (pred(*first, *last) ? first : last)
				: sprout::detail::adjacent_find_impl_ra(
					sprout::next(first, pivot), last, pred,
					(sprout::distance(first, last) - pivot) / 2,
					sprout::detail::adjacent_find_impl_ra(
						first, sprout::next(first, pivot), pred,
						pivot / 2,
						first
						)
					)
				;
		}
		template<typename RandomAccessIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			RandomAccessIterator
		>::type
		adjacent_find(
			RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first == last || sprout::distance(first, last) == 1 ? last
				: adjacent_find_impl_check_ra(
					sprout::detail::adjacent_find_impl_ra(
						first, sprout::next(first, sprout::distance(first, last) - 1), pred,
						(sprout::distance(first, last) - 1) / 2, first
						),
					last
					)
				;
		}

		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR ForwardIterator
		adjacent_find_impl_check(sprout::tuples::tuple<ForwardIterator, ForwardIterator, bool> const& current) {
			return !sprout::tuples::get<2>(current) ? sprout::tuples::get<1>(current)
				: sprout::tuples::get<0>(current)
				;
		}
		template<typename ForwardIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<ForwardIterator, ForwardIterator, bool>
		adjacent_find_impl_1(
			sprout::tuples::tuple<ForwardIterator, ForwardIterator, bool> const& current,
			ForwardIterator last, BinaryPredicate pred, typename std::iterator_traits<ForwardIterator>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<ForwardIterator, ForwardIterator, bool> type;
			return sprout::tuples::get<2>(current) || sprout::tuples::get<1>(current) == last ? current
				: n == 1 ? pred(*sprout::tuples::get<0>(current), *sprout::tuples::get<1>(current))
					? type(sprout::tuples::get<0>(current), sprout::tuples::get<1>(current), true)
					: type(sprout::tuples::get<1>(current), sprout::next(sprout::tuples::get<1>(current)), false)
				: sprout::detail::adjacent_find_impl_1(
					sprout::detail::adjacent_find_impl_1(
						current,
						last, pred, n / 2
						),
					last, pred, n - n / 2
					)
				;
		}
		template<typename ForwardIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<ForwardIterator, ForwardIterator, bool>
		adjacent_find_impl(
			sprout::tuples::tuple<ForwardIterator, ForwardIterator, bool> const& current,
			ForwardIterator last, BinaryPredicate pred, typename std::iterator_traits<ForwardIterator>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<ForwardIterator, ForwardIterator, bool> type;
			return sprout::tuples::get<2>(current) || sprout::tuples::get<1>(current) == last ? current
				: sprout::detail::adjacent_find_impl(
					sprout::detail::adjacent_find_impl_1(
						current,
						last, pred, n
						),
					last, pred, n * 2
					)
				;
		}
		template<typename ForwardIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator
		adjacent_find(
			ForwardIterator first, ForwardIterator last, BinaryPredicate pred,
			void*
			)
		{
			typedef sprout::tuples::tuple<ForwardIterator, ForwardIterator, bool> type;
			return first == last ? last
				: sprout::detail::adjacent_find_impl_check(
					sprout::detail::adjacent_find_impl(type(first, sprout::next(first), false), last, pred, 1)
					)
				;
		}
	}	//namespace detail

	// 25.2.8 Adjacent find
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator
	adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred) {
		typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
		return sprout::detail::adjacent_find(first, last, pred, category());
	}

	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	adjacent_find(ForwardIterator first, ForwardIterator last) {
		return sprout::adjacent_find(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::equal_to<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_ADJACENT_FIND_HPP
