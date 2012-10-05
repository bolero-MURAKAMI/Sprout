#ifndef SPROUT_DETAIL_ALGORITHM_SET_OVERLAP_COUNT_HPP
#define SPROUT_DETAIL_ALGORITHM_SET_OVERLAP_COUNT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace detail {
		//
		// set_overlap_count
		//
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator1>::difference_type
		set_overlap_count(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Compare comp
			)
		{
			return first1 != last1 && first2 != last2
				? comp(*first1, *first2)
					? sprout::detail::set_overlap_count(sprout::next(first1), last1, first2, last2, comp)
					: comp(*first2, *first1)
						? sprout::detail::set_overlap_count(first1, last1, sprout::next(first2), last2, comp)
						: 1 + sprout::detail::set_overlap_count(sprout::next(first1), last1, sprout::next(first2), last2, comp)
				: 0
				;
		}
		//
		// set_overlap_count
		//
		template<typename InputIterator1, typename InputIterator2>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator1>::difference_type
		set_overlap_count(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2
			)
		{
			return first1 != last1 && first2 != last2
				? *first1 < *first2
					? sprout::detail::set_overlap_count(sprout::next(first1), last1, first2, last2)
					: *first2 < *first1
						? sprout::detail::set_overlap_count(first1, last1, sprout::next(first2), last2)
						: 1 + sprout::detail::set_overlap_count(sprout::next(first1), last1, sprout::next(first2), last2)
				: 0
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_SET_OVERLAP_COUNT_HPP
