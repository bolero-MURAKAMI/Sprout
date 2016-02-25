/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_FIT_SINUSOID_HPP
#define SPROUT_NUMERIC_DFT_FIT_SINUSOID_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/dft/fixed/sinusoid.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/pit/pit.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
			sinusoid_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::value_type const& frequency,
				typename sprout::container_traits<Container>::value_type const& amplitude,
				typename sprout::container_traits<Container>::value_type const& phase,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::sinusoid(cont, frequency, amplitude, phase)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// sinusoid
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
		sinusoid(
			Container const& cont,
			typename sprout::container_traits<Container>::value_type const& frequency = 1,
			typename sprout::container_traits<Container>::value_type const& amplitude = 1,
			typename sprout::container_traits<Container>::value_type const& phase = 0
			)
		{
			return sprout::fit::detail::sinusoid_impl(cont, frequency, amplitude, phase, sprout::internal_begin_offset(cont));
		}

		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
		sinusoid(
			typename sprout::container_traits<Container>::value_type const& frequency = 1,
			typename sprout::container_traits<Container>::value_type const& amplitude = 1,
			typename sprout::container_traits<Container>::value_type const& phase = 0
			)
		{
			return sprout::fit::sinusoid(sprout::pit<Container>(), frequency, amplitude, phase);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIT_SINUSOID_HPP
