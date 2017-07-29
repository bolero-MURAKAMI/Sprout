/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_IO_HPP
#define SPROUT_STRING_IO_HPP

#include <istream>
#include <ostream>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/string/string.hpp>

namespace sprout {
	//
	// operator>>
	// operator<<
	//
	template<typename T, std::size_t N, typename Traits, typename StreamTraits>
	inline SPROUT_NON_CONSTEXPR std::basic_istream<T, StreamTraits>&
	operator>>(std::basic_istream<T, StreamTraits>& lhs, sprout::basic_string<T, N, Traits>& rhs) {
		typedef T elem_type;
		typedef StreamTraits traits_type;
		typedef std::basic_istream<T, StreamTraits> istream_type;
		typedef sprout::basic_string<T, N, Traits> string_type;
		typedef std::ctype<elem_type> ctype_type;
		typedef typename string_type::size_type size_type;
		std::ios_base::iostate state = std::ios_base::goodbit;
		bool changed = false;
		size_type current = 0;
		if (typename istream_type::sentry(lhs)) {
			ctype_type const& ctype_fac = std::use_facet<ctype_type>(lhs.getloc());
			try {
				size_type remain = 0 < lhs.width() && static_cast<size_type>(lhs.width()) < rhs.max_size()
					? static_cast<size_type>(lhs.width())
					: rhs.max_size()
					;
				typename traits_type::int_type meta = lhs.rdbuf()->sgetc();
				for (; remain; --remain, meta = lhs.rdbuf()->snextc())
					if (traits_type::eq_int_type(traits_type::eof(), meta)) {
						state |= std::ios_base::eofbit;
						break;
					} else if (ctype_fac.is(ctype_type::space, traits_type::to_char_type(meta))) {
						break;
					} else {
						rhs[current] = traits_type::to_char_type(meta);
						changed = true;
						++current;
					}
			} catch (...) {
				state |= std::ios_base::badbit;
			}
		}
		lhs.width(0);
		if (!changed) {
			state |= std::ios_base::failbit;
		}
		lhs.setstate(state);
		rhs.resize(current);
		return lhs;
	}
	template<typename T, std::size_t N, typename Traits, typename StreamTraits>
	inline SPROUT_NON_CONSTEXPR std::basic_ostream<T, StreamTraits>&
	operator<<(std::basic_ostream<T, StreamTraits>& lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return lhs << rhs.c_str();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_IO_HPP
