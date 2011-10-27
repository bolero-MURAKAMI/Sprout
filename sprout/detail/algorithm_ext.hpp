#ifndef SPROUT_DETAIL_ALGORITHM_EXT_HPP
#define SPROUT_DETAIL_ALGORITHM_EXT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace detail {
		//
		// count_n
		//
		template<typename InputIterator, typename Size, typename T>
		SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type count_n(
			InputIterator first,
			Size n,
			T const& value
			)
		{
			return n == 0
				? 0
				: (*first == value ? 1 : 0) + sprout::detail::count_n(sprout::next(first), n - 1, value)
				;
		}

		//
		// count_n_if
		//
		template<typename InputIterator, typename Size, typename Predicate>
		SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type count_n_if(
			InputIterator first,
			Size n,
			Predicate pred
			)
		{
			return n == 0
				? 0
				: (pred(*first) ? 1 : 0) + sprout::detail::count_n_if(sprout::next(first), n - 1, pred)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_EXT_HPP
