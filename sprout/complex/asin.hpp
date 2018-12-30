/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_ASIN_HPP
#define SPROUT_COMPLEX_ASIN_HPP

#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/arithmetic_operators.hpp>
#include <sprout/complex/perp.hpp>
#include <sprout/complex/asinh.hpp>

namespace sprout {
	//
	// asin
	//
	// casin(z) = -i casinh(iz)
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	asin(sprout::complex<T> const& x) {
		return -sprout::perp(sprout::asinh(sprout::perp(x)));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_ASIN_HPP
