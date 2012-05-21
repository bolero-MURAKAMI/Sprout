#ifndef SPROUT_FUNCTIONAL_LESS_EQUAL_HPP
#define SPROUT_FUNCTIONAL_LESS_EQUAL_HPP

#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 20.8.5 Comparisons
	template<typename T>
	struct less_equal {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& x, T const& y) const {
				return x <= y;
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_LESS_EQUAL_HPP
