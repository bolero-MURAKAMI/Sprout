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
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/detail/integer.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/bit/shlr.hpp>

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
		template<std::size_t N, typename Integral>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			(N == 1),
			sprout::pair<Integral, int>
		>::type
		ctz_bytes(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			return xn;
		}
		template<std::size_t N, typename Integral>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			(N > 1),
			sprout::pair<Integral, int>
		>::type
		ctz_bytes(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			typedef sprout::pair<Integral, int> type;
			return sprout::detail::ctz_bytes<N / 2>(
				(xn.first & static_cast<Integral>(sprout::numeric_limits<typename sprout::detail::uint_t<N / 2 * CHAR_BIT>::least>::max())) ? xn
					: type(sprout::shlr(xn.first, N / 2 * CHAR_BIT), xn.second + N / 2 * CHAR_BIT)
				);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR sprout::pair<Integral, int>
		ctz_bytes(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			return sprout::detail::ctz_bytes<sizeof(Integral)>(xn);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		ctz_bits1(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			return (xn.first & Integral(0x1ul)) ? xn.second
				: xn.second + 1
				;
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		ctz_bits2(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			typedef sprout::pair<Integral, int> type;
			return sprout::detail::ctz_bits1(
				(xn.first & Integral(0x3ul)) ? xn
					: type(sprout::shlr(xn.first, 2), xn.second + 2)
				);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		ctz_bits4(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			typedef sprout::pair<Integral, int> type;
			return sprout::detail::ctz_bits2(
				(xn.first & Integral(0xful)) ? xn
					: type(sprout::shlr(xn.first, 4), xn.second + 4)
				);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		ctz_bits(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			return sprout::detail::ctz_bits4(xn);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		ctz_non0(Integral x) SPROUT_NOEXCEPT {
			typedef sprout::pair<Integral, int> type;
			return sprout::detail::ctz_bits(sprout::detail::ctz_bytes(type(x, 0)));
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		ctz(Integral x) SPROUT_NOEXCEPT {
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
	ctz(Integral x) SPROUT_NOEXCEPT {
		return sprout::detail::ctz(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_CTZ_HPP
