/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_CTZ_HPP
#define SPROUT_BIT_CTZ_HPP

#include <climits>
#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
#	if SPROUT_USE_BUILTIN_BIT_OPERATION
		inline SPROUT_CONSTEXPR int
		ctz_non0(unsigned x) {
			return __builtin_ctz(x);
		}
		inline SPROUT_CONSTEXPR int
		ctz_non0(unsigned long x) {
			return __builtin_ctzl(x);
		}
		inline SPROUT_CONSTEXPR int
		ctz_non0(unsigned long long x) {
			return __builtin_ctzll(x);
		}
#	endif
		template<typename Integral>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_unsigned<Integral>::value,
			int
		>::type
		ctz_non0(Integral x) {
			return x & 1 ? 0
				: 1 + sprout::detail::ctz_non0(static_cast<Integral>(x >> 1))
				;
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_signed<Integral>::value,
			int
		>::type
		ctz_non0(Integral x) {
			return sprout::detail::ctz_non0(static_cast<typename std::make_unsigned<Integral>::type>(x));
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		ctz(Integral x) {
			return x == 0 ? static_cast<int>(sizeof(x) * CHAR_BIT)
				: sprout::detail::ctz_non0(x)
				;
		}
	}	// namespace detail
	//
	// ctz
	//
	template<typename Integral>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<Integral>::value,
		int
	>::type
	ctz(Integral x) {
		return sprout::detail::ctz(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_CTZ_HPP
