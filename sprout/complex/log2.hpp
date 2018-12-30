/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_LOG2_HPP
#define SPROUT_COMPLEX_LOG2_HPP

#include <sprout/config.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/arithmetic_operators.hpp>
#include <sprout/complex/log.hpp>

namespace sprout {
	//
	// log2
	//
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		log2_impl(sprout::complex<T> const& z) {
			return sprout::math::isnan(z.real()) || sprout::math::isnan(z.imag()) ? z
				: z / sprout::math::ln_two<T>()
				;
		}
	}	// namespace detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	log2(sprout::complex<T> const& x) {
		return sprout::detail::log2_impl(sprout::log(x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_LOG2_HPP
