/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_COS_HPP
#define SPROUT_COMPLEX_COS_HPP

#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/perp.hpp>
#include <sprout/complex/cosh.hpp>

namespace sprout {
	//
	// cos
	//
	// ccos(z) = ccosh(iz)
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	cos(sprout::complex<T> const& x) {
		return sprout::cosh(sprout::perp(x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_COS_HPP
