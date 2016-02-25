/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDLIB_ABS_HPP
#define SPROUT_CSTDLIB_ABS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/is_signed.hpp>
#include <sprout/type_traits/is_unsigned.hpp>

namespace sprout {

	// 7.20.6.1 absÅClabsÅCãyÇ— llabs ä÷êî
	inline SPROUT_CONSTEXPR int
	abs(int j) {
		return j < 0 ? -j : j;
	}

	inline SPROUT_CONSTEXPR long
	labs(long j) {
		return j < 0 ? -j : j;
	}

	inline SPROUT_CONSTEXPR long long
	llabs(long long j) {
		return j < 0 ? -j : j;
	}

	inline SPROUT_CONSTEXPR long
	abs(long j) {
		return sprout::labs(j);
	}

	inline SPROUT_CONSTEXPR long long
	abs(long long j) {
		return sprout::llabs(j);
	}

	namespace {
		template<typename IntType>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_integral<IntType>::value && sprout::is_signed<IntType>::value,
			IntType
		>::type
		abs(IntType j) {
			return j < 0 ? -j : j;
		}

		template<typename IntType>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_integral<IntType>::value && sprout::is_unsigned<IntType>::value,
			IntType
		>::type
		abs(IntType j) {
			return j;
		}
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_ABS_HPP
