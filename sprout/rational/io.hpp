/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RATIONAL_IO_HPP
#define SPROUT_RATIONAL_IO_HPP

#include <istream>
#include <ostream>
#include <sprout/config.hpp>
#include <sprout/rational/rational.hpp>
#include <sprout/detail/io/ios_state.hpp>

namespace sprout {
	//
	// operator>>
	// operator<<
	//
	template<typename Elem, typename Traits, typename IntType>
	inline SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>&
	operator>>(std::basic_istream<Elem, Traits>& lhs, sprout::rational<IntType>& rhs) {
		IntType n = IntType(0);
		IntType d = IntType(1);
		Elem c = 0;
		sprout::detail::io::ios_flags_saver saver(lhs);
		lhs >> n;
		c = lhs.get();
		if (c != Elem('/')) {
			lhs.clear(std::istream::badbit);
		}
		lhs >> std::noskipws;
		lhs >> d;
		if (lhs) {
			rhs.assign(n, d);
		}
		return lhs;
	}
	template<typename Elem, typename Traits, typename IntType>
	inline SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>&
	operator<<(std::basic_ostream<Elem, Traits>& lhs, sprout::rational<IntType> const& rhs) {
		return lhs << rhs.numerator() << Elem('/') << rhs.denominator();
	}
}	// namespace sprout

#endif	// SPROUT_RATIONAL_IO_HPP
