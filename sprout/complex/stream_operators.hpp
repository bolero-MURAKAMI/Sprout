/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_STREAM_OPERATORS_HPP
#define SPROUT_COMPLEX_STREAM_OPERATORS_HPP

#include <istream>
#include <ostream>
#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>

namespace sprout {
	template<typename T, typename Char, typename Traits>
	inline SPROUT_NON_CONSTEXPR std::basic_istream<Char, Traits>&
	operator>>(std::basic_istream<Char, Traits>& lhs, sprout::complex<T>& rhs) {
		T re, im;
		Char ch;
		lhs >> ch;
		if (ch == '(') {
			lhs >> re >> ch;
			if (ch == ',') {
				lhs >> im >> ch;
				if (ch == ')') {
					rhs = sprout::complex<T>(re, im);
				} else {
					lhs.setstate(std::ios_base::failbit);
				}
			} else if (ch == ')') {
				rhs = re;
			} else {
				lhs.setstate(std::ios_base::failbit);
			}
		} else {
			lhs.putback(ch);
			lhs >> re;
			rhs = re;
		}
		return lhs;
	}
	template<typename T, typename Char, typename Traits>
	inline SPROUT_NON_CONSTEXPR std::basic_ostream<Char, Traits>&
	operator<<(std::basic_ostream<Char, Traits>& lhs, sprout::complex<T> const& rhs) {
		return lhs << '(' << rhs.real() << ',' << rhs.imag() << ')';
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_STREAM_OPERATORS_HPP
