#ifndef SPROUT_DETAIL_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
#define SPROUT_DETAIL_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP

#include <sprout/config.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/iterator/next.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename Compare>
		inline SPROUT_CONSTEXPR int
		lexicographical_compare_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator2 first2, Compare comp,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type size,
			int found
			)
		{
			return found != 2 ? found
				: size == 1 ? comp(*first1, *first2) ? -1 : comp(*first2, *first1) ? 1 : 2
				: sprout::detail::lexicographical_compare_impl_ra(
					sprout::next(first1, size / 2), sprout::next(first2, size / 2), comp, size - size / 2,
					sprout::detail::lexicographical_compare_impl_ra(
						first1, first2, comp, size / 2,
						2
						)
					)
				;
		}

		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		lexicographical_compare_impl_1(
			sprout::pair<InputIterator1, InputIterator2> const& current,
			InputIterator1 last1, InputIterator2 last2, Compare comp,
			typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator1, InputIterator2> type;
			return current.second == last2 || current.first == last1 ? current
				: n == 1 ? comp(*current.first, *current.second) ? type(last1, current.second)
					: comp(*current.second, *current.first) ? type(current.first, last2)
					: type(sprout::next(current.first), sprout::next(current.second))
				: sprout::detail::lexicographical_compare_impl_1(
					sprout::detail::lexicographical_compare_impl_1(
						current,
						last1, last2, comp, n / 2
						),
					last1, last2, comp, n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		lexicographical_compare_impl(
			sprout::pair<InputIterator1, InputIterator2> const& current,
			InputIterator1 last1, InputIterator2 last2, Compare comp,
			typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			return current.second == last2 || current.first == last1 ? current
				: sprout::detail::lexicographical_compare_impl(
					sprout::detail::lexicographical_compare_impl_1(
						current,
						last1, last2, comp, n
						),
					last1, last2, comp, n * 2
					)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif /* #ifndef SPROUT_DETAIL_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP */
