/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_CLRSB_HPP
#define SPROUT_BIT_CLRSB_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/bit/clz.hpp>

namespace sprout {
	namespace detail {
#	if SPROUT_USE_BUILTIN_BIT_OPERATION
		inline SPROUT_CONSTEXPR int
		clrsb(unsigned x) {
			return __builtin_clrsb(x);
		}
		inline SPROUT_CONSTEXPR int
		clrsb(unsigned long x) {
			return __builtin_clrsbl(x);
		}
		inline SPROUT_CONSTEXPR int
		clrsb(unsigned long long x) {
			return __builtin_clrsbll(x);
		}
#	endif
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		clrsb(Integral x) SPROUT_NOEXCEPT {
			return sprout::clz(~x);
		}
	}	// namespace detail
	//
	// clrsb
	//
	template<typename Integral>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<Integral>::value,
		int
	>::type
	clrsb(Integral x) SPROUT_NOEXCEPT {
		return sprout::detail::clrsb(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_CLRSB_HPP
