/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INTEGER_CARRY_TO_EXP2_HPP
#define SPROUT_INTEGER_CARRY_TO_EXP2_HPP

#include <climits>
#include <limits>
#include <sprout/config.hpp>
#include <sprout/bit/cntl0.hpp>
#include <sprout/bit/popcount.hpp>
#include <sprout/type_traits/is_sint.hpp>
#include <sprout/type_traits/is_uint.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace detail {
		template<typename IntType>
		inline SPROUT_CONSTEXPR IntType
		carry_to_exp2_simpl(IntType x) {
			return sprout::popcount(x) <= 1 ? x
				: IntType(1) << (sizeof(IntType) * CHAR_BIT - sprout::cntl0(x))
				;
		}
		template<typename UIntType>
		inline SPROUT_CONSTEXPR UIntType
		carry_to_exp2_uimpl(int n) {
			return !n ? UIntType(0)
				: UIntType(1) << (sizeof(UIntType) * CHAR_BIT - n)
				;
		}
	}	// namespace detail
	//
	// carry_to_exp2
	//
	// note: for signed integer
	//	x == MIN
	//		--> carry_to_exp2(x) returns x .
	//	x < 0
	//		--> carry_to_exp2(x) returns -carry_to_exp2(-x) .
	//	-(MIN / 2) < x
	//		--> carry_to_exp2(x) returns MIN .
	//
	// note: for unsigned integer
	//	MAX / 2 + 1 < x
	//		--> carry_to_exp2(x) returns 0 .
	//
	template<
		typename IntType,
		typename sprout::enabler_if<sprout::is_sint<IntType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR IntType
	carry_to_exp2(IntType x) {
		return x == std::numeric_limits<IntType>::min() ? x
			: x < IntType(0) ? -sprout::detail::carry_to_exp2_simpl(-x)
			: sprout::detail::carry_to_exp2_simpl(x)
			;
	}
	template<
		typename UIntType,
		typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR UIntType
	carry_to_exp2(UIntType x) {
		return sprout::popcount(x) <= 1 ? x
			: sprout::detail::carry_to_exp2_uimpl<UIntType>(sprout::cntl0(x))
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_INTEGER_CARRY_TO_EXP2_HPP
