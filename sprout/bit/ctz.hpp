/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_CTZ_HPP
#define SPROUT_BIT_CTZ_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
#	if SPROUT_USE_BUILTIN_BIT_OPERATION
		inline SPROUT_CONSTEXPR int
		ctz(unsigned n) {
			return __builtin_ctz(n);
		}
		inline SPROUT_CONSTEXPR int
		ctz(unsigned long n) {
			return __builtin_ctzl(n);
		}
		inline SPROUT_CONSTEXPR int
		ctz(unsigned long long n) {
			return __builtin_ctzll(n);
		}
#	endif
		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_unsigned<T>::value,
			int
		>::type
		ctz(T n) {
			return n & 1 ? 0
				: 1 + sprout::detail::ctz(static_cast<T>(n >> 1))
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_signed<T>::value,
			int
		>::type
		ctz(T n) {
			return sprout::detail::ctz(static_cast<typename std::make_unsigned<T>::type>(n));
		}
	}	// namespace detail
	//
	// ctz
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<T>::value,
		int
	>::type
	ctz(T n) {
		return sprout::detail::ctz(n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_CTZ_HPP
