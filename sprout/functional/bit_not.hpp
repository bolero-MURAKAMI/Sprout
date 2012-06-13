#ifndef SPROUT_FUNCTIONAL_BIT_NOT_HPP
#define SPROUT_FUNCTIONAL_BIT_NOT_HPP

#include <sprout/config.hpp>

namespace sprout {
	// 20.8.7 bitwise operations
	template<typename T>
	struct bit_not {
	public:
		typedef T argument_type;
		typedef T result_type;
	public:
		SPROUT_CONSTEXPR T operator()(T const& x) const {
				return ~x;
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BIT_NOT_HPP
