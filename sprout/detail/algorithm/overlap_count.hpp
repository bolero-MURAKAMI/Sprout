#ifndef SPROUT_DETAIL_ALGORITHM_OVERLAP_COUNT_HPP
#define SPROUT_DETAIL_ALGORITHM_OVERLAP_COUNT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT
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
						(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - pivot) / 2
						)
				;
		}
		template<typename RandomAccessIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<RandomAccessIterator>::difference_type
		overlap_count(
			RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first == last || NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) == 1 ? 0
				: sprout::detail::overlap_count_impl_ra(
					first, sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - 1), pred,
					(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - 1) / 2
					)
				;
		}

		template<typename InputIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		overlap_count_impl(
			InputIterator first, InputIterator last, BinaryPredicate pred,
			typename std::iterator_traits<InputIterator>::value_type const& value
			)
		{
			return first == last ? 0
				: pred(*first, value) ? 1 + sprout::detail::overlap_count_impl(sprout::next(first), last, pred, value)
				: sprout::detail::overlap_count_impl(sprout::next(first), last, pred, *first)
				;
		}
		template<typename InputIterator, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		overlap_count_impl(
			InputIterator first, InputIterator last, BinaryPredicate pred,
			void*
			)
		{
			return first == last ? 0
				: sprout::detail::overlap_count_impl(sprout::next(first), last, pred, *first)
				;
		}

		//
		// overlap_count
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
