/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RATIONAL_VALUES_HPP
#define SPROUT_RATIONAL_VALUES_HPP

#include <sprout/config.hpp>
#include <sprout/rational/rational.hpp>
#include <sprout/cstdlib/abs.hpp>

namespace sprout {
	//
	// abs
	//
	template<typename IntType>
	inline SPROUT_CONSTEXPR sprout::rational<IntType>
	abs(sprout::rational<IntType> const& x) {
		return x.numerator() >= IntType(0) ? x
			: sprout::detail::rational_construct_access<IntType>::raw_construct(
				-x.numerator(), x.denominator()
				)
			;
	}
}	// namespace sprout

#endif	// SPROUT_RATIONAL_VALUES_HPP
