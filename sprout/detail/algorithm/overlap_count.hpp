#ifndef SPROUT_DETAIL_ALGORITHM_OVERLAP_COUNT_HPP
#define SPROUT_DETAIL_ALGORITHM_OVERLAP_COUNT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<RandomAccessIterator>::difference_type
		overlap_count_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? (pred(*first, *last) ? 1 : 0)
				: sprout::detail::overlap_count_impl_ra(
					first, sprout::next(first, pivot), pred,
					pivot / 2
					)
					+ sprout::detail::overlap_count_impl_ra(
						sprout::next(first, pivot), last, pred,
						(sprout::distance(first, last) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type
		>::type
		overlap_count(
			RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first == last || sprout::distance(first, last) == 1 ? 0
				: sprout::detail::overlap_count_impl_ra(
					first, sprout::next(first, sprout::distance(first, last) - 1), pred,
					(sprout::distance(first, last) - 1) / 2
					)
				;
		}

		template<typename InputIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator, typename std::iterator_traits<InputIterator>::value_type, typename std::iterator_traits<InputIterator>::difference_type>
		overlap_count_impl_1(
			sprout::tuples::tuple<InputIterator, typename std::iterator_traits<InputIterator>::value_type, typename std::iterator_traits<InputIterator>::difference_type> const& current,
			InputIterator last, BinaryPredicate pred, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator, typename std::iterator_traits<InputIterator>::value_type, typename std::iterator_traits<InputIterator>::difference_type> type;
			return sprout::tuples::get<0>(current) == last ? current
				: n == 1 ? type(
					sprout::next(sprout::tuples::get<0>(current)), *sprout::tuples::get<0>(current),
					sprout::tuples::get<2>(current) + (pred(*sprout::tuples::get<0>(current), sprout::tuples::get<1>(current)) ? 1 : 0)
					)
				: sprout::detail::overlap_count_impl_1(
					sprout::detail::overlap_count_impl_1(
						current,
						last, pred, n / 2
						),
					last, pred, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator, typename std::iterator_traits<InputIterator>::value_type, typename std::iterator_traits<InputIterator>::difference_type>
		overlap_count_impl(
			sprout::tuples::tuple<InputIterator, typename std::iterator_traits<InputIterator>::value_type, typename std::iterator_traits<InputIterator>::difference_type> const& current,
			InputIterator last, BinaryPredicate pred, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator, typename std::iterator_traits<InputIterator>::value_type, typename std::iterator_traits<InputIterator>::difference_type> type;
			return sprout::tuples::get<0>(current) == last ? current
				: sprout::detail::overlap_count_impl(
					sprout::detail::overlap_count_impl_1(
						current,
						last, pred, n
						),
					last, pred, n * 2
					)
				;
		}
		template<typename InputIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		overlap_count(
			InputIterator first, InputIterator last, BinaryPredicate pred,
			void*
			)
		{
			typedef sprout::tuples::tuple<InputIterator, typename std::iterator_traits<InputIterator>::value_type, typename std::iterator_traits<InputIterator>::difference_type> type;
			return first == last ? 0
				: sprout::tuples::get<2>(
					sprout::detail::overlap_count_impl(type(sprout::next(first), *first, 0), last, pred, 1)
					)
				;
		}

		//
		// overlap_count
		//
		//	recursion depth:
		//		O(log N)
		//
		template<typename InputIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		overlap_count(InputIterator first, InputIterator last, BinaryPredicate pred) {
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::detail::overlap_count(first, last, pred, category());
		}

		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		overlap_count(InputIterator first, InputIterator last) {
			return sprout::detail::overlap_count(
				first, last,
				NS_SSCRISK_CEL_OR_SPROUT::equal_to<typename std::iterator_traits<InputIterator>::value_type>()
				);
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_OVERLAP_COUNT_HPP
