#ifndef SPROUT_DETAIL_OVERLAP_COUNT_HPP
#define SPROUT_DETAIL_OVERLAP_COUNT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace detail {
		template<typename Iterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type overlap_count_impl(
			Iterator first,
			Iterator last,
			typename std::iterator_traits<Iterator>::value_type const& value,
			typename std::iterator_traits<Iterator>::difference_type current = 0
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
		template<typename Iterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type overlap_count(
			Iterator first,
			Iterator last
			)
		{
			return first == last
				? 0
				: sprout::detail::overlap_count_impl(sprout::next(first), last, *first)
				;
		}

		template<typename Iterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type overlap_count_impl(
			Iterator first,
			Iterator last,
			Predicate pred,
			typename std::iterator_traits<Iterator>::value_type const& value
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
		template<typename Iterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type overlap_count(
			Iterator first,
			Iterator last,
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

#endif	// #ifndef SPROUT_DETAIL_OVERLAP_COUNT_HPP
