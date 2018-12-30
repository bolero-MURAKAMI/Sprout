/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_SET_UNION_HPP
#define SPROUT_ALGORITHM_FIT_SET_UNION_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/set_union.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/detail/algorithm/set_overlap_count.hpp>
#include <sprout/iterator/type_traits/category.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			set_union_impl(
				InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2,
				Result const& result, Compare comp,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::set_union(first1, last1, first2, last2, result, comp)),
					offset,
					offset + sprout::fit_size(
						result, sprout::distance(first1, last1) + sprout::distance(first2, last2) - sprout::detail::set_overlap_count(first1, last1, first2, last2, comp)
						)
					);
			}
		}	// namespace detail
		//
		// set_union
		//
		template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		set_union(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Result const& result, Compare comp
			)
		{
			static_assert(
				sprout::is_forward_iterator<InputIterator1>::value && sprout::is_forward_iterator<InputIterator2>::value,
				"Sorry, not implemented."
				);
			return sprout::fit::detail::set_union_impl(first1, last1, first2, last2, result, comp, sprout::internal_begin_offset(result));
		}

		namespace detail {
			template<typename InputIterator1, typename InputIterator2, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			set_union_impl(
				InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2,
				Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::set_union(first1, last1, first2, last2, result)),
					offset,
					offset + sprout::fit_size(
						result, sprout::distance(first1, last1) + sprout::distance(first2, last2) - sprout::detail::set_overlap_count(first1, last1, first2, last2)
						)
					);
			}
		}	// namespace detail
		//
		// set_union
		//
		template<typename InputIterator1, typename InputIterator2, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		set_union(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Result const& result
			)
		{
			static_assert(
				sprout::is_forward_iterator<InputIterator1>::value && sprout::is_forward_iterator<InputIterator2>::value,
				"Sorry, not implemented."
				);
			return sprout::fit::detail::set_union_impl(first1, last1, first2, last2, result, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_SET_UNION_HPP
