/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_EULER_HPP
#define SPROUT_COMPLEX_EULER_HPP

#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/cos.hpp>

namespace sprout {
	//
	// euler
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	euler(T const& theta) {
		return sprout::complex<T>(sprout::math::cos(theta), sprout::math::sin(theta));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_EULER_HPP
