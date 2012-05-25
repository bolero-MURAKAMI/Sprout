#ifndef SPROUT_CSTDLIB_ABS_HPP
#define SPROUT_CSTDLIB_ABS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/enabler_if.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 7.20.6.1  absÅClabsÅCãyÇ— llabs ä÷êî
	SPROUT_CONSTEXPR int abs(int j) {
		return j < 0 ? -j : j;
	}

	SPROUT_CONSTEXPR long labs(long j) {
		return j < 0 ? -j : j;
	}

	SPROUT_CONSTEXPR long long llabs(long long j) {
		return j < 0 ? -j : j;
	}

	SPROUT_CONSTEXPR long abs(long j) {
		return sprout::labs(j);
	}

	SPROUT_CONSTEXPR long long abs(long long j) {
		return sprout::llabs(j);
	}

	template<
		typename IntType,
		typename sprout::enabler_if<
			std::is_integral<IntType>::value && std::is_signed<IntType>::value
		>::type = sprout::enabler
	>
	SPROUT_CONSTEXPR IntType abs(IntType j) {
		return j < 0 ? -j : j;
	}
	template<
		typename IntType,
		typename sprout::enabler_if<
			std::is_integral<IntType>::value && std::is_unsigned<IntType>::value
		>::type = sprout::enabler
	>
	SPROUT_CONSTEXPR IntType abs(IntType j) {
		return j;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_ABS_HPP
