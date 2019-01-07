/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_GENERATE_HPP
#define SPROUT_ALGORITHM_FIT_GENERATE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/generate.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Generator>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
			generate_impl(
				Container const& cont, Generator const& gen,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::generate(cont, gen)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// generate
		//
		template<typename Container, typename Generator>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
		generate(Container const& cont, Generator const& gen) {
			return sprout::fit::detail::generate_impl(cont, gen, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_GENERATE_HPP
