/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_DETAIL_COPYSIGN_MUL_HPP
#define SPROUT_COMPLEX_DETAIL_COPYSIGN_MUL_HPP

#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		copysign_mul(T const& t, sprout::complex<T> const& z) {
			return sprout::complex<T>(
				sprout::math::copysign(t, z.real()),
				sprout::math::copysign(t, z.imag())
				);
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_DETAIL_COPYSIGN_MUL_HPP
