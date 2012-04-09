#ifndef SPROUT_FUNCTIONAL_BIT_AND_HPP
#define SPROUT_FUNCTIONAL_BIT_AND_HPP

#include <sprout/config.hpp>

namespace sprout {
	// 20.8.7 bitwise operations
	template<typename T>
	struct bit_and {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef T result_type;
	public:
		SPROUT_CONSTEXPR T operator()(T const& x, T const& y) const {
			 return x & y;
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BIT_AND_HPP
