#ifndef SPROUT_DETAIL_ALGORITHM_OVERLAP_COUNT_HPP
#define SPROUT_DETAIL_ALGORITHM_OVERLAP_COUNT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type overlap_count_impl(
			InputIterator first,
			InputIterator last,
			typename std::iterator_traits<InputIterator>::value_type const& value,
			typename std::iterator_traits<InputIterator>::difference_type current = 0
			)
		{
			return first == last
				? 0
				: *first == value
				? 1 + sprout::detail::overlap_count_impl(sprout::next(first), last, value)
				: sprout::detail::overlap_count_impl(sprout::next(first), last, *first)
				;
		}
		//
		// overlap_count
		//
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type overlap_count(
			InputIterator first,
			InputIterator last
			)
		{
			return first == last
				? 0
				: sprout::detail::overlap_count_impl(sprout::next(first), last, *first)
				;
		}

		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type overlap_count_impl(
			InputIterator first,
			InputIterator last,
			Predicate pred,
			typename std::iterator_traits<InputIterator>::value_type const& value
			)
		{
			return first == last
				? 0
				: pred(*first, value)
				? 1 + sprout::detail::overlap_count_impl(sprout::next(first), last, pred, value)
				: sprout::detail::overlap_count_impl(sprout::next(first), last, pred, *first)
				;
		}
		//
		// overlap_count
		//
		template<typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type overlap_count(
			InputIterator first,
			InputIterator last,
			Predicate pred
			)
		{
			return first == last
				? 0
				: sprout::detail::overlap_count_impl(sprout::next(first), last, pred, *first)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_OVERLAP_COUNT_HPP
