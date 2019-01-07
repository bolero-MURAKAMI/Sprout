/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_RECURRENCE_N_HPP
#define SPROUT_ALGORITHM_FIT_RECURRENCE_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/recurrence_n.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Size, typename Generator, typename... Inits>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
			recurrence_n_impl(
				Container const& cont, Size n, Generator const& gen,
				typename sprout::container_traits<Container>::difference_type offset,
				Inits const&... inits
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::recurrence_n(cont, n, gen, inits...)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min<typename sprout::container_traits<Container>::difference_type>(n, sprout::size(cont))
					);
			}
		}	// namespace detail
		//
		// recurrence_n
		//
		template<typename Container, typename Size, typename Generator, typename... Inits>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
		recurrence_n(Container const& cont, Size n, Generator const& gen, Inits const&... inits) {
			return sprout::fit::detail::recurrence_n_impl(cont, n, gen, sprout::internal_begin_offset(cont), inits...);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_RECURRENCE_N_HPP
