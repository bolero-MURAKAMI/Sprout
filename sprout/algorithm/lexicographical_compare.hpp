/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
#define SPROUT_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/detail/algorithm/lexicographical_compare.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/functional/less.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename Difference1, typename Difference2>
		inline SPROUT_CONSTEXPR bool
		lexicographical_compare_impl_check(
			Difference1 size1, Difference2 size2,
			int found
			)
		{
			return found < 0 || (found == 2 && size1 < size2);
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
				: sprout::detail::lexicographical_compare_impl_check(
					sprout::distance(first1, last1), sprout::distance(first2, last2),
					sprout::detail::lexicographical_compare_impl_ra(
						first1, first2, comp,
						NS_SSCRISK_CEL_OR_SPROUT::min(sprout::distance(first1, last1), sprout::distance(first2, last2)),
						2
						)
					)
				;
		}

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
