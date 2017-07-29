/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_UNFOLD_HPP
#define SPROUT_ALGORITHM_FIT_UNFOLD_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/unfold.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Generator, typename Init>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
			unfold_impl(
				Container const& cont, Generator const& gen, Init const& init,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::unfold(cont, gen, init)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// unfold
		//
		template<typename Container, typename Generator, typename Init>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
		unfold(Container const& cont, Generator const& gen, Init const& init) {
			return sprout::fit::detail::unfold_impl(cont, gen, init, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_UNFOLD_HPP
