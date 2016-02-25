/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_REMOVE_COPY_HPP
#define SPROUT_ALGORITHM_FIT_REMOVE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/count.hpp>
#include <sprout/algorithm/fixed/remove_copy.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/iterator/type_traits/category.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			remove_copy_impl(
				InputIterator first, InputIterator last, Result const& result, T const& value,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::remove_copy(first, last, result, value)),
					offset,
					offset + sprout::fit_size(result, sprout::distance(first, last) - sprout::count(first, last, value))
					);
			}
		}	// namespace detail
		//
		// remove_copy
		//
		template<typename InputIterator, typename Result, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		remove_copy(InputIterator first, InputIterator last, Result const& result, T const& value) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::remove_copy_impl(first, last, result, value, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REMOVE_COPY_HPP
