/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_FIT_IOTA_HPP
#define SPROUT_NUMERIC_FIT_IOTA_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/fixed/iota.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
			iota_impl(
				Container const& cont, T const& value,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::iota(cont, value)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// iota
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
		iota(Container const& cont, T const& value) {
			return sprout::fit::detail::iota_impl(cont, value, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FIT_IOTA_HPP
