/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_PARITY_HPP
#define SPROUT_BIT_PARITY_HPP

#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/bit/shlr.hpp>

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
		template<std::size_t N, typename Integral>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			(N == 1),
			Integral
		>::type
		parity_bytes(Integral x) SPROUT_NOEXCEPT {
			return x;
		}
		template<std::size_t N, typename Integral>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			(N > 1),
			Integral
		>::type
		parity_bytes(Integral x) SPROUT_NOEXCEPT {
			return sprout::detail::parity_bytes<N / 2>(
				x ^ sprout::shlr(x, N / 2 * CHAR_BIT)
				);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR Integral
		parity_bytes(Integral x) SPROUT_NOEXCEPT {
			return sprout::detail::parity_bytes<sizeof(Integral)>(x);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR Integral
		parity_bits4(Integral x) SPROUT_NOEXCEPT {
			return x ^ sprout::shlr(x, 4);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR Integral
		parity_bits2(Integral x) SPROUT_NOEXCEPT {
			return sprout::detail::parity_bits4(
				x ^ sprout::shlr(x, 2)
				);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR Integral
		parity_bits1(Integral x) SPROUT_NOEXCEPT {
			return sprout::detail::parity_bits2(
				x ^ sprout::shlr(x, 1)
				);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR Integral
		parity_bits(Integral x) SPROUT_NOEXCEPT {
			return sprout::detail::parity_bits1(x);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		parity(Integral x) {
			return static_cast<int>(sprout::detail::parity_bytes(sprout::detail::parity_bits(x))) & 1;
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
