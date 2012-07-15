#ifndef SPROUT_DETAIL_ALGORITHM_COUNT_N_IF_HPP
#define SPROUT_DETAIL_ALGORITHM_COUNT_N_IF_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace detail {
		//
		// count_n_if
		//
		template<typename InputIterator, typename Size, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type count_n_if(
			InputIterator first,
			Size n,
			Predicate pred
			)
		{
			return n == 0 ? 0
				: (pred(*first) ? 1 : 0) + sprout::detail::count_n_if(sprout::next(first), n - 1, pred)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_COUNT_N_IF_HPP
