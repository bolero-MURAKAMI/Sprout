/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_CLZ_HPP
#define SPROUT_BIT_CLZ_HPP

#include <cstddef>
#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/bit/shlr.hpp>
#include <sprout/bit/shll.hpp>

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
		template<std::size_t N, typename Integral>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			(N == 1),
			sprout::pair<Integral, int>
		>::type
		clz_bytes(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			return xn;
		}
		template<std::size_t N, typename Integral>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			(N > 1),
			sprout::pair<Integral, int>
		>::type
		clz_bytes(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			typedef sprout::pair<Integral, int> type;
			return sprout::detail::clz_bytes<N / 2>(
				sprout::shlr(xn.first, (sizeof(Integral) - N / 2) * CHAR_BIT) ? xn
					: type(sprout::shll(xn.first, N / 2 * CHAR_BIT), xn.second + N / 2 * CHAR_BIT)
				);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR sprout::pair<Integral, int>
		clz_bytes(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			return sprout::detail::clz_bytes<sizeof(Integral)>(xn);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		clz_bits1(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			return xn.second - sprout::shlr(xn.first, sizeof(Integral) * CHAR_BIT - 1);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		clz_bits2(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			typedef sprout::pair<Integral, int> type;
			return sprout::detail::clz_bits1(
				sprout::shlr(xn.first, sizeof(Integral) * CHAR_BIT - 2) ? xn
					: type(sprout::shll(xn.first, 2), xn.second + 2)
				);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		clz_bits4(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			typedef sprout::pair<Integral, int> type;
			return sprout::detail::clz_bits2(
				sprout::shlr(xn.first, sizeof(Integral) * CHAR_BIT - 4) ? xn
					: type(sprout::shll(xn.first, 4), xn.second + 4)
				);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		clz_bits(sprout::pair<Integral, int> const& xn) SPROUT_NOEXCEPT {
			return sprout::detail::clz_bits4(xn);
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		clz_non0(Integral x) SPROUT_NOEXCEPT {
			typedef sprout::pair<Integral, int> type;
			return sprout::detail::clz_bits(sprout::detail::clz_bytes(type(x, 1)));
		}
		template<typename Integral>
		inline SPROUT_CONSTEXPR int
		clz(Integral x) SPROUT_NOEXCEPT {
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
	clz(Integral x) SPROUT_NOEXCEPT {
		return sprout::detail::clz(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_CLZ_HPP
