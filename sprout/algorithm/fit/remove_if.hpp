/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_REMOVE_IF_HPP
#define SPROUT_ALGORITHM_FIT_REMOVE_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/count_if.hpp>
#include <sprout/algorithm/fixed/remove_if.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
			remove_if_impl(
				Container const& cont, Predicate pred,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::remove_if(cont, pred)),
					offset,
					offset + sprout::size(cont) - sprout::count_if(sprout::begin(cont), sprout::end(cont), pred)
					);
			}
		}	// namespace detail
		//
		// remove_if
		//
		template<typename Container, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
		remove_if(Container const& cont, Predicate pred) {
			return sprout::fit::detail::remove_if_impl(cont, pred, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REMOVE_IF_HPP
