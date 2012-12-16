#ifndef SPROUT_DETAIL_ALGORITHM_COUNT_N_HPP
#define SPROUT_DETAIL_ALGORITHM_COUNT_N_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/count.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator, typename Size, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_n(
			InputIterator first, Size n, T const& value,
			std::random_access_iterator_tag*
			)
		{
			return sprout::count(first, sprout::next(first, n), value);
		}

		template<typename InputIterator, typename Size, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_n_impl(InputIterator first, Size n, T const& value) {
			return n == 0 ? 0
				: (*first == value ? 1 : 0) + sprout::detail::count_n_impl(sprout::next(first), n - 1, value)
				;
		}
		template<typename InputIterator, typename Size, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_n(
			InputIterator first, Size n, T const& value,
			void*
			)
		{
			return sprout::detail::count_n_impl(first, n, value);
		}

		//
		// count_n
		//
		template<typename InputIterator, typename Size, typename T>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		count_n(InputIterator first, Size n, T const& value) {
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::detail::count_n(first, n, value, category());
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ALGORITHM_COUNT_N_HPP
