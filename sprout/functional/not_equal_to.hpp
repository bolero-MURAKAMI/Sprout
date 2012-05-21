#ifndef SPROUT_FUNCTIONAL_NOT_EQUAL_TO_HPP
#define SPROUT_FUNCTIONAL_NOT_EQUAL_TO_HPP

#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 20.8.5 Comparisons
	template<typename T>
	struct not_equal_to {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& x, T const& y) const {
				return x != y;
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_NOT_EQUAL_TO_HPP
