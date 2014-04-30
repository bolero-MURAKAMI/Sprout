/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BITSET_IO_HPP
#define SPROUT_BITSET_IO_HPP

#include <string>
#include <iosfwd>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/bitset/bitset.hpp>

namespace sprout {
	// 20.5.4 bitset operators:

	template<typename Char, typename Traits, std::size_t N>
	inline SPROUT_NON_CONSTEXPR std::basic_istream<Char, Traits>&
	operator>>(std::basic_istream<Char, Traits>& lhs, sprout::bitset<N>& rhs) {
		typedef typename Traits::char_type char_type;
		typedef std::basic_istream<Char, Traits> istream_type;
		typedef typename istream_type::ios_base ios_base;

		std::basic_string<Char, Traits> tmp;
		tmp.reserve(N);
		char_type const zero = lhs.widen('0');
		char_type const one = lhs.widen('1');
		typename ios_base::iostate state = ios_base::goodbit;
		typename istream_type::sentry sentry(lhs);
		if (sentry) {
			try {
				for (std::size_t i = N; i > 0; --i) {
					static typename Traits::int_type eof = Traits::eof();
					typename Traits::int_type c1 = lhs.rdbuf()->sbumpc();
					if (Traits::eq_int_type(c1, eof)) {
						state |= ios_base::eofbit;
						break;
					} else {
						char_type const c2 = Traits::to_char_type(c1);
						if (Traits::eq(c2, zero)) {
							tmp.push_back(zero);
						} else if (Traits::eq(c2, one)) {
							tmp.push_back(one);
						} else if (Traits::eq_int_type(lhs.rdbuf()->sputbackc(c2), eof)) {
							state |= ios_base::failbit;
							break;
						}
					}
				}
			} catch(...) {
				lhs.setstate(ios_base::badbit);
			}
		}
		if (tmp.empty() && N) {
			state |= ios_base::failbit;
		} else {
			rhs.copy_from_string(tmp, static_cast<std::size_t>(0), N, zero, one);
			if (state) {
				lhs.setstate(state);
				return lhs;
			}
		}
		return lhs;
	}
	template<typename Char, typename Traits, std::size_t N>
	inline SPROUT_NON_CONSTEXPR std::basic_ostream<Char, Traits>&
	operator<<(std::basic_ostream<Char, Traits>& lhs, sprout::bitset<N> const& rhs) {
		std::basic_string<Char, Traits> tmp;
		std::ctype<Char> const& ct = std::use_facet<std::ctype<Char> >(lhs.getloc());
		rhs.copy_to_string(tmp, ct.widen('0'), ct.widen('1'));
		return lhs << tmp;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BITSET_IO_HPP
