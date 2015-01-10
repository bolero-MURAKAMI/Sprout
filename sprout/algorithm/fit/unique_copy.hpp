/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_UNIQUE_COPY_HPP
#define SPROUT_ALGORITHM_FIT_UNIQUE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/unique_copy.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/detail/algorithm/overlap_count.hpp>
#include <sprout/iterator/type_traits/category.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			unique_copy_impl(
				InputIterator first, InputIterator last, Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::unique_copy(first, last, result)),
					offset,
					offset + sprout::fit_size(result, sprout::distance(first, last) - sprout::detail::overlap_count(first, last))
					);
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		unique_copy(InputIterator first, InputIterator last, Result const& result) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::unique_copy_impl(first, last, result, sprout::internal_begin_offset(result));
		}

		namespace detail {
			template<typename InputIterator, typename Result, typename BinaryPredicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			unique_copy_impl(
				InputIterator first, InputIterator last, Result const& result, BinaryPredicate pred,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::unique_copy(first, last, result, pred)),
					offset,
					offset + sprout::fit_size(result, sprout::distance(first, last) - sprout::detail::overlap_count(first, last, pred))
					);
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename InputIterator, typename Result, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		unique_copy(InputIterator first, InputIterator last, Result const& result, BinaryPredicate pred) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::unique_copy_impl(first, last, result, pred, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_UNIQUE_COPY_HPP
