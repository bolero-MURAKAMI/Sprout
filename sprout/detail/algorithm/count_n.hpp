#ifndef SPROUT_DETAIL_ALGORITHM_COUNT_N_HPP
#define SPROUT_DETAIL_ALGORITHM_COUNT_N_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace detail {
		//
		// count_n
		//
		template<typename InputIterator, typename Size, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type count_n(
			InputIterator first,
			Size n,
			T const& value
			)
		{
			return n == 0 ? 0
				: (*first == value ? 1 : 0) + sprout::detail::count_n(sprout::next(first), n - 1, value)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_COUNT_N_HPP
