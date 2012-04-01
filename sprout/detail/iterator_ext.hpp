#ifndef SPROUT_DETAIL_ITERATOR_EXT_HPP
#define SPROUT_DETAIL_ITERATOR_EXT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace detail {
		template<typename Iterator>
		SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type bidirectional_distance_impl(
			Iterator first1,
			Iterator first2,
			Iterator last,
			typename std::iterator_traits<Iterator>::difference_type current = 1
			)
		{
			return first1 == last ? current
				: first2 == last ? -current
				: sprout::detail::bidirectional_distance_impl(sprout::next(first1), sprout::prev(first2), last, current + 1)
				;
		}

		//
		// bidirectional_distance
		//
		template<typename Iterator>
		SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type bidirectional_distance(
			Iterator first,
			Iterator last
			)
		{
			return first == last ? 0
				: sprout::detail::bidirectional_distance_impl(sprout::next(first), sprout::prev(first), last)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ITERATOR_EXT_HPP
