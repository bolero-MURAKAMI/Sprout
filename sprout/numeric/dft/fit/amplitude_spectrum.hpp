/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_FIT_AMPLITUDE_SPECTRUM_HPP
#define SPROUT_NUMERIC_DFT_FIT_AMPLITUDE_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/dft/fixed/amplitude_spectrum.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/iterator/type_traits/category.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			amplitude_spectrum_impl(
				InputIterator const& first, InputIterator const& last, Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::amplitude_spectrum(first, last, result)),
					offset,
					offset + sprout::fit_size(result, sprout::distance(first, last))
					);
			}
		}	// namespace detail
		//
		// amplitude_spectrum
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		amplitude_spectrum(InputIterator first, InputIterator last, Result const& result) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::amplitude_spectrum_impl(first, last, result, sprout::internal_begin_offset(result));
		}

		template<typename Result, typename InputIterator>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		amplitude_spectrum(InputIterator first, InputIterator last) {
			return sprout::fit::amplitude_spectrum(first, last, sprout::pit<Result>());
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIT_AMPLITUDE_SPECTRUM_HPP
