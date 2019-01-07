/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_FIT_SQUARE_HPP
#define SPROUT_NUMERIC_DFT_FIT_SQUARE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/dft/fixed/square.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/pit/pit.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
			square_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::value_type const& frequency,
				typename sprout::container_traits<Container>::value_type const& amplitude,
				typename sprout::container_traits<Container>::value_type const& phase,
				typename sprout::container_traits<Container>::value_type const& duty,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::square(cont, frequency, amplitude, phase, duty)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// square
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
		square(
			Container const& cont,
			typename sprout::container_traits<Container>::value_type const& frequency = 1,
			typename sprout::container_traits<Container>::value_type const& amplitude = 1,
			typename sprout::container_traits<Container>::value_type const& phase = 0,
			typename sprout::container_traits<Container>::value_type const& duty = 0.5
			)
		{
			return sprout::fit::detail::square_impl(cont, frequency, amplitude, phase, duty, sprout::internal_begin_offset(cont));
		}

		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
		square(
			typename sprout::container_traits<Container>::value_type const& frequency = 1,
			typename sprout::container_traits<Container>::value_type const& amplitude = 1,
			typename sprout::container_traits<Container>::value_type const& phase = 0,
			typename sprout::container_traits<Container>::value_type const& duty = 0.5
			)
		{
			return sprout::fit::square(sprout::pit<Container>(), frequency, amplitude, phase, duty);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIT_SQUARE_HPP
