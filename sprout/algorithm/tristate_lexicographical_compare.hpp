#ifndef SPROUT_ALGORITHM_TRISTATE_LEXICOGRAPHICAL_COMPARE_HPP
#define SPROUT_ALGORITHM_TRISTATE_LEXICOGRAPHICAL_COMPARE_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/utility/pair.hpp>
#include <sprout/algorithm/min.hpp>
#include <sprout/functional/less.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare_impl_ra_2(
			RandomAccessIterator1 last1, RandomAccessIterator2 last2, Compare comp,
			sprout::pair<RandomAccessIterator1, RandomAccessIterator2> const& found
			)
		{
			return found.second == last2 ? (found.first == last1 ? 0 : 1)
				: found.first == last1 ? -1
				: comp(*found.first, *found.second) ? -1
				: comp(*found.second, *found.first) ? 1
				: 0
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<RandomAccessIterator1, RandomAccessIterator2>
		tristate_lexicographical_compare_impl_ra_1(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, Compare comp,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, sprout::pair<RandomAccessIterator1, RandomAccessIterator2> const& found
			)
		{
			typedef sprout::pair<RandomAccessIterator1, RandomAccessIterator2> found_type;
			return found.first != first1 ? found
				: pivot == 0 ? (comp(*first1, *first2) || comp(*first2, *first1) ? found_type(first1, first2) : found_type(last1, last2))
				: sprout::detail::tristate_lexicographical_compare_impl_ra_1(
					sprout::next(first1, pivot), last1, sprout::next(first2, pivot), last2, comp,
					(sprout::distance(first1, last1) - pivot) / 2,
					sprout::detail::tristate_lexicographical_compare_impl_ra_1(
						first1, sprout::next(first1, pivot), first2, sprout::next(first2, pivot), comp,
						pivot / 2,
						found_type(first1, first2)
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, Compare comp,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type size
			)
		{
			typedef sprout::pair<RandomAccessIterator1, RandomAccessIterator2> found_type;
			return sprout::detail::tristate_lexicographical_compare_impl_ra_2(
				last1, last2, comp,
				sprout::detail::tristate_lexicographical_compare_impl_ra_1(
					first1, sprout::next(first1, size), first2, sprout::next(first2, size), comp,
					size / 2, found_type(first1, first2)
					)
				);
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, RandomAccessIterator2 last2, Compare comp,
			std::random_access_iterator_tag*
			)
		{
			return first2 == last2 ? (first1 == last1 ? 0 : 1)
				: first1 == last1 ? -1
				: sprout::detail::tristate_lexicographical_compare_impl_ra(
					first1, last1, first2, last2, comp,
					sprout::min(sprout::distance(first1, last1), sprout::distance(first2, last2))
					)
				;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare_impl(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
			return first2 == last2 ? (first1 == last1 ? 0 : 1)
				: first1 == last1 || comp(*first1, *first2) ? -1
				: comp(*first2, *first1) ? 1
				: sprout::detail::tristate_lexicographical_compare_impl(sprout::next(first1), last1, sprout::next(first2), last2, comp)
				;
		}
		template<typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare(
			InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp,
			void*
			)
		{
			return sprout::detail::tristate_lexicographical_compare_impl(first1, last1, first2, last2, comp);
		}
	}	// namespace detail

	//
	// tristate_lexicographical_compare
	//
	//	recursion depth:
	//		[first1, last1), [first2, last2) are RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
	//
	template<typename InputIterator1, typename InputIterator2, typename Compare>
	inline SPROUT_CONSTEXPR int
	tristate_lexicographical_compare(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		Compare comp
		)
	{
		typedef typename sprout::common_iterator_category<InputIterator1, InputIterator2>::type* category;
		return sprout::detail::tristate_lexicographical_compare(first1, last1, first2, last2, comp, category());
	}

	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR int
	tristate_lexicographical_compare(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2
		)
	{
		return sprout::tristate_lexicographical_compare(
			first1, last1, first2, last2,
			sprout::less<>()
			);
	}

	namespace detail {
		template<typename RandomAccessIterator1, typename T1, typename RandomAccessIterator2, typename T2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare_2_impl_ra_2(
			RandomAccessIterator1 last1, T1 const& delim1, RandomAccessIterator2 last2, T2 const& delim2, Compare comp,
			sprout::pair<RandomAccessIterator1, RandomAccessIterator2> const& found
			)
		{
			return found.second == last2 || (!comp(*found.second, delim2) && !comp(delim2, *found.second))
					? (found.first == last1 || (!comp(*found.first, delim1) && !comp(delim1, *found.first)) ? 0 : 1)
				: found.first == last1 || (!comp(*found.first, delim1) && !comp(delim1, *found.first)) ? -1
				: comp(*found.first, *found.second) ? -1
				: comp(*found.second, *found.first) ? 1
				: 0
				;
		}
		template<typename RandomAccessIterator1, typename T1, typename RandomAccessIterator2, typename T2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<RandomAccessIterator1, RandomAccessIterator2>
		tristate_lexicographical_compare_2_impl_ra_1(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, T1 const& delim1,
			RandomAccessIterator2 first2, RandomAccessIterator2 last2, T2 const& delim2,
			Compare comp,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot, sprout::pair<RandomAccessIterator1, RandomAccessIterator2> const& found
			)
		{
			typedef sprout::pair<RandomAccessIterator1, RandomAccessIterator2> found_type;
			return found.first != first1 ? found
				: pivot == 0 ? (
					comp(*first1, *first2) || comp(*first2, *first1) || (!comp(*first1, delim1) && !comp(delim1, *first1)) || (!comp(*first2, delim2) && !comp(delim2, *first2))
						? found_type(first1, first2) : found_type(last1, last2)
					)
				: sprout::detail::tristate_lexicographical_compare_2_impl_ra_1(
					sprout::next(first1, pivot), last1, delim1, sprout::next(first2, pivot), last2, delim2, comp,
					(sprout::distance(first1, last1) - pivot) / 2,
					sprout::detail::tristate_lexicographical_compare_2_impl_ra_1(
						first1, sprout::next(first1, pivot), delim1, first2, sprout::next(first2, pivot), delim2, comp,
						pivot / 2,
						found_type(first1, first2)
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename T1, typename RandomAccessIterator2, typename T2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare_2_impl_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, T1 const& delim1,
			RandomAccessIterator2 first2, RandomAccessIterator2 last2, T2 const& delim2,
			Compare comp,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type size
			)
		{
			typedef sprout::pair<RandomAccessIterator1, RandomAccessIterator2> found_type;
			return sprout::detail::tristate_lexicographical_compare_2_impl_ra_2(
				last1, delim1, last2, delim2, comp,
				sprout::detail::tristate_lexicographical_compare_2_impl_ra_1(
					first1, sprout::next(first1, size), delim1, first2, sprout::next(first2, size), delim2, comp,
					size / 2, found_type(first1, first2)
					)
				);
		}
		template<typename RandomAccessIterator1, typename T1, typename RandomAccessIterator2, typename T2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare_2(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, T1 const& delim1,
			RandomAccessIterator2 first2, RandomAccessIterator2 last2, T2 const& delim2,
			Compare comp,
			std::random_access_iterator_tag*
			)
		{
			return first2 == last2 || (!comp(*first2, delim2) && !comp(delim2, *first2)) ? (first1 == last1 || (!comp(*first1, delim1) && !comp(delim1, *first1)) ? 0 : 1)
				: first1 == last1 || (!comp(*first1, delim1) && !comp(delim1, *first1)) ? -1
				: sprout::detail::tristate_lexicographical_compare_2_impl_ra(
					first1, last1, delim1, first2, last2, delim2, comp,
					sprout::min(sprout::distance(first1, last1), sprout::distance(first2, last2))
					)
				;
		}

		template<typename InputIterator1, typename T1, typename InputIterator2, typename T2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare_2_impl(
			InputIterator1 first1, InputIterator1 last1, T1 const& delim1,
			InputIterator2 first2, InputIterator2 last2, T2 const& delim2,
			Compare comp
			)
		{
			return first2 == last2 || (!comp(*first2, delim2) && !comp(delim2, *first2)) ? (first1 == last1 || (!comp(*first1, delim1) && !comp(delim1, *first1)) ? 0 : 1)
				: first1 == last1 || (!comp(*first1, delim1) && !comp(delim1, *first1)) || comp(*first1, *first2) ? -1
				: comp(*first2, *first1) ? 1
				: sprout::detail::tristate_lexicographical_compare_2_impl(sprout::next(first1), last1, delim1, sprout::next(first2), last2, delim2, comp)
				;
		}
		template<typename InputIterator1, typename T1, typename InputIterator2, typename T2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare_2(
			InputIterator1 first1, InputIterator1 last1, T1 const& delim1,
			InputIterator2 first2, InputIterator2 last2, T2 const& delim2,
			Compare comp,
			void*
			)
		{
			return sprout::detail::tristate_lexicographical_compare_2_impl(first1, last1, delim1, first2, last2, delim2, comp);
		}
	}	// namespace detail

	//
	// tristate_lexicographical_compare
	//
	//	recursion depth:
	//		[first1, last1), [first2, last2) are RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
	//
	template<typename InputIterator1, typename T1, typename InputIterator2, typename T2, typename Compare>
	inline SPROUT_CONSTEXPR int
	tristate_lexicographical_compare(
		InputIterator1 first1, InputIterator1 last1, T1 const& delim1,
		InputIterator2 first2, InputIterator2 last2, T2 const& delim2,
		Compare comp
		)
	{
		typedef typename sprout::common_iterator_category<InputIterator1, InputIterator2>::type* category;
		return sprout::detail::tristate_lexicographical_compare_2(first1, last1, delim1, first2, last2, delim2, comp, category());
	}

	template<typename InputIterator1, typename T1, typename InputIterator2, typename T2>
	inline SPROUT_CONSTEXPR int
	tristate_lexicographical_compare(
		InputIterator1 first1, InputIterator1 last1, T1 const& delim1,
		InputIterator2 first2, InputIterator2 last2, T2 const& delim2
		)
	{
		return sprout::tristate_lexicographical_compare(
			first1, last1, delim1, first2, last2, delim2,
			sprout::less<>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_TRISTATE_LEXICOGRAPHICAL_COMPARE_HPP
