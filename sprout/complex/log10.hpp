/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_LOG10_HPP
#define SPROUT_COMPLEX_LOG10_HPP

#include <sprout/config.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/operators.hpp>
#include <sprout/complex/log.hpp>

namespace sprout {
	//
	// log10
	//
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		log10_impl(sprout::complex<T> const& z) {
			return sprout::math::isnan(z.real()) || sprout::math::isnan(z.imag()) ? z
				: z / sprout::math::ln_ten<T>()
				;
		}
	}	// namespace detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	log10(sprout::complex<T> const& x) {
		return sprout::detail::log10_impl(sprout::log(x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_LOG10_HPP
