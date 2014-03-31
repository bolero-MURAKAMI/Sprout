/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_PARITY_HPP
#define SPROUT_BIT_PARITY_HPP

#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/bit/popcount.hpp>

namespace sprout {
	namespace detail {
#	if SPROUT_USE_BUILTIN_BIT_OPERATION
		inline SPROUT_CONSTEXPR int
		parity(unsigned x) {
			return __builtin_parity(x);
		}
		inline SPROUT_CONSTEXPR int
		parity(unsigned long x) {
			return __builtin_parityl(x);
		}
		inline SPROUT_CONSTEXPR int
		parity(unsigned long long x) {
			return __builtin_parityll(x);
		}
#	endif
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		parity(Integral x) {
			return sprout::popcount(x) & 1;
		}
	}	// namespace detail
	//
	// parity
	//
	template<typename Integral>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<Integral>::value,
		int
	>::type
	parity(Integral x) {
		return sprout::detail::parity(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_PARITY_HPP
