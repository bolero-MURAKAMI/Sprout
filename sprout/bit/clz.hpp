/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_CLZ_HPP
#define SPROUT_BIT_CLZ_HPP

#include <climits>
#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
#	if SPROUT_USE_BUILTIN_BIT_OPERATION
		inline SPROUT_CONSTEXPR int
		clz_non0(unsigned x) {
			return __builtin_clz(x);
		}
		inline SPROUT_CONSTEXPR int
		clz_non0(unsigned long x) {
			return __builtin_clzl(x);
		}
		inline SPROUT_CONSTEXPR int
		clz_non0(unsigned long long x) {
			return __builtin_clzll(x);
		}
#	endif
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		clz_non0_impl(Integral x, Integral m = Integral(1) << (CHAR_BIT * sizeof(Integral) - 1)) {
			return m == 0 || x & m ? 0
				: 1 + sprout::detail::clz_non0_impl(x, static_cast<Integral>(m >> 1))
				;
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_unsigned<Integral>::value,
			int
		>::type
		clz_non0(Integral x) {
			return sprout::detail::clz_non0_impl(static_cast<Integral>(x));
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_signed<Integral>::value,
			int
		>::type
		clz_non0(Integral x) {
			return sprout::detail::clz_non0(static_cast<typename std::make_unsigned<Integral>::type>(x));
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		clz(Integral x) {
			return x == 0 ? static_cast<int>(sizeof(x) * CHAR_BIT)
				: sprout::detail::clz_non0(x)
				;
		}
	}	// namespace detail
	//
	// clz
	//
	template<typename Integral>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<Integral>::value,
		int
	>::type
	clz(Integral x) {
		return sprout::detail::clz(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_CLZ_HPP
