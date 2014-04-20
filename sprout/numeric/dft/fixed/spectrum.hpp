/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_FIXED_SPECTRUM_HPP
#define SPROUT_NUMERIC_DFT_FIXED_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/numeric/dft/fixed/amplitude_spectrum.hpp>
#include <sprout/numeric/dft/fixed/phase_spectrum.hpp>

namespace sprout {
	namespace fixed {
		//
		// spectrum
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		spectrum(InputIterator first, InputIterator last, Result const& result) {
			return sprout::fixed::amplitude_spectrum(first, last, result);
		}

		template<typename Result, typename InputIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		spectrum(InputIterator first, InputIterator last) {
			return sprout::fixed::amplitude_spectrum<Result>(first, last);
		}
	}	// namespace fixed

	template<
		typename InputIterator, typename Result,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	spectrum(InputIterator first, InputIterator last, Result const& result) {
		return sprout::fixed::spectrum(first, last, result);
	}

	template<typename Result, typename InputIterator>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	spectrum(InputIterator first, InputIterator last) {
		return sprout::fixed::spectrum<Result>(first, last);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIXED_SPECTRUM_HPP
