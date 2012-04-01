#ifndef SPROUT_CSTDLIB_ABS_HPP
#define SPROUT_CSTDLIB_ABS_HPP

#include <sprout/config.hpp>

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
		return labs(j);
	}

	SPROUT_CONSTEXPR long long abs(long long j) {
		return llabs(j);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_ABS_HPP
