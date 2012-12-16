#ifndef SPROUT_DETAIL_ALGORITHM_COUNT_N_IF_HPP
#define SPROUT_DETAIL_ALGORITHM_COUNT_N_IF_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/count_if.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator, typename Size, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_n_if(
			InputIterator first, Size n, Predicate pred,
			std::random_access_iterator_tag*
			)
		{
			return sprout::count_if(first, sprout::next(first, n), pred);
		}

		template<typename InputIterator, typename Size, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_n_if_impl(InputIterator first, Size n, Predicate pred) {
			return n == 0 ? 0
				: (pred(*first) ? 1 : 0) + sprout::detail::count_n_if(sprout::next(first), n - 1, pred)
				;
		}
		template<typename InputIterator, typename Size, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_n_if(
			InputIterator first, Size n, Predicate pred,
			void*
			)
		{
			return sprout::detail::count_n_if_impl(first, n, pred);
		}

		//
		// count_n_if
		//
		template<typename InputIterator, typename Size, typename Predicate>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_n_if(InputIterator first, Size n, Predicate pred) {
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::detail::count_n_if(first, n, pred, category());

		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_COUNT_N_IF_HPP
