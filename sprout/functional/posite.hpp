#ifndef SPROUT_FUNCTIONAL_POSITE_HPP
#define SPROUT_FUNCTIONAL_POSITE_HPP

#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 20.8.4 Arithmetic operations
	template<typename T>
	struct posite {
	public:
		typedef T argument_type;
		typedef T result_type;
	public:
		SPROUT_CONSTEXPR T operator()(T const& x) const {
				return +x;
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POSITE_HPP
