#ifndef SPROUT_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
#define SPROUT_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/algorithm/min.hpp>
#include <sprout/functional/less.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR bool
		lexicographical_compare_impl_check(
			InputIterator1 last1, InputIterator2 last2, Compare comp,
			sprout::pair<InputIterator1, InputIterator2> const& found
			)
		{
			return found.second == last2 ? false
				: found.first == last1 || comp(*found.first, *found.second)
				;
		}

		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<RandomAccessIterator1, RandomAccessIterator2>
		lexicographical_compare_impl_ra_1(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, Compare comp,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, sprout::pair<RandomAccessIterator1, RandomAccessIterator2> const& found
			)
		{
			typedef sprout::pair<RandomAccessIterator1, RandomAccessIterator2> found_type;
			return found.first != first1 ? found
				: pivot == 0 ? (comp(*first1, *first2) || comp(*first2, *first1) ? found_type(first1, first2) : found_type(last1, last2))
				: sprout::detail::lexicographical_compare_impl_ra_1(
					sprout::next(first1, pivot), last1, sprout::next(first2, pivot), last2, comp,
					(sprout::distance(first1, last1) - pivot) / 2,
					sprout::detail::lexicographical_compare_impl_ra_1(
						first1, sprout::next(first1, pivot), first2, sprout::next(first2, pivot), comp,
						pivot / 2,
						found_type(first1, first2)
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename Compare>
		inline SPROUT_CONSTEXPR bool
		lexicographical_compare_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, Compare comp,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type size
			)
		{
			typedef sprout::pair<RandomAccessIterator1, RandomAccessIterator2> found_type;
			return sprout::detail::lexicographical_compare_impl_check(
				last1, last2, comp,
				sprout::detail::lexicographical_compare_impl_ra_1(
					first1, sprout::next(first1, size), first2, sprout::next(first2, size), comp,
					size / 2, found_type(first1, first2)
					)
				);
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename Compare>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value,
			bool
		>::type
		lexicographical_compare(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, Compare comp,
			std::random_access_iterator_tag*
			)
		{
			return first2 == last2 ? false
				: first1 == last1 ? true
				: sprout::detail::lexicographical_compare_impl_ra(
					first1, last1, first2, last2, comp,
					sprout::min(sprout::distance(first1, last1), sprout::distance(first2, last2))
					)
				;
		}

		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, InputIterator2>
		lexicographical_compare_impl_1(
			sprout::pair<InputIterator1, InputIterator2> current,
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
			sprout::pair<InputIterator1, InputIterator2> current,
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
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR bool
		lexicographical_compare(
			InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp,
			std::input_iterator_tag*
			)
		{
			typedef sprout::pair<InputIterator1, InputIterator2> type;
			return sprout::detail::lexicographical_compare_impl_check(
				last1, last2, comp,
				sprout::detail::lexicographical_compare_impl(type(first1, first2), last1, last2, comp, 1)
				);
		}
	}	// namespace detail

	// 25.4.8 Lexicographical comparison
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	template<typename InputIterator1, typename InputIterator2, typename Compare>
	inline SPROUT_CONSTEXPR bool
	lexicographical_compare(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		Compare comp
		)
	{
		typedef typename sprout::common_iterator_category<InputIterator1, InputIterator2>::type* category;
		return sprout::detail::lexicographical_compare(first1, last1, first2, last2, comp, category());
	}

	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR bool
	lexicographical_compare(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2
		)
	{
		return sprout::lexicographical_compare(
			first1, last1, first2, last2,
			sprout::less<>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
