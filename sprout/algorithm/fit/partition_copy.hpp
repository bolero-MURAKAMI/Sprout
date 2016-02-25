/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_FIT_PARTITION_COPY_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/partition_copy.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/detail/algorithm/count_n_if.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT
#include <sprout/iterator/type_traits/category.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			partition_copy_impl(
				InputIterator first, InputIterator last, Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				typedef typename std::iterator_traits<InputIterator>::difference_type diff_type;
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::partition_copy(first, last, result, pred)),
					offset,
					offset + sprout::fit_size(
						result, sprout::detail::count_n_if(first, NS_SSCRISK_CEL_OR_SPROUT::min<diff_type>(sprout::distance(first, last), sprout::size(result)), pred)
						)
					);
			}
		}	// namespace detail
		//
		// partition_copy
		//
		template<typename InputIterator, typename Result, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		partition_copy(InputIterator first, InputIterator last, Result const& result, Predicate pred) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::partition_copy_impl(first, last, result, pred, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_PARTITION_COPY_HPP
