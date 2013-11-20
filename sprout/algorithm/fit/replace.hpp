/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_REPLACE_HPP
#define SPROUT_ALGORITHM_FIT_REPLACE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/replace.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
			replace_impl(
				Container const& cont, T const& old_value, T const& new_value,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::replace(cont, old_value, new_value)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// replace
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
		replace(Container const& cont, T const& old_value, T const& new_value) {
			return sprout::fit::detail::replace_impl(cont, old_value, new_value, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REPLACE_HPP
