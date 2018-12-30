/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_HASH_STD_COMPLEX_HPP
#define SPROUT_FUNCTIONAL_HASH_STD_COMPLEX_HPP

#include <complex>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(std::complex<T> const& v) {
		return sprout::hash_values(v.real(), v.imag());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_STD_COMPLEX_HPP
