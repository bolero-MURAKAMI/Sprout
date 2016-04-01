/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_REVERSE_COPY_HPP
#define SPROUT_ALGORITHM_FIT_REVERSE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/reverse_copy.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename BidirectionalIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			reverse_copy_impl(
				BidirectionalIterator const& first, BidirectionalIterator const& last, Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::reverse_copy(first, last, result)),
					offset,
					offset + sprout::fit_size(result, sprout::distance(first, last))
					);
			}
		}	// namespace detail
		//
		// reverse_copy
		//
		template<typename BidirectionalIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		reverse_copy(BidirectionalIterator first, BidirectionalIterator last, Result const& result) {
			return sprout::fit::detail::reverse_copy_impl(first, last, result, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REVERSE_COPY_HPP
