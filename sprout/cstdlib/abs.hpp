#ifndef SPROUT_CSTDLIB_ABS_HPP
#define SPROUT_CSTDLIB_ABS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 7.20.6.1  absÅClabsÅCãyÇ— llabs ä÷êî
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
		template<
			typename IntType,
			typename sprout::enabler_if<
				std::is_integral<IntType>::value && std::is_signed<IntType>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR IntType
		abs(IntType j) {
			return j < 0 ? -j : j;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<
				std::is_integral<IntType>::value && std::is_unsigned<IntType>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR IntType
		abs(IntType j) {
			return j;
		}
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_ABS_HPP
