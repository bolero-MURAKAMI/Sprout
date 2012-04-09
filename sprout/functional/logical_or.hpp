#ifndef SPROUT_FUNCTIONAL_LOGICAL_OR_HPP
#define SPROUT_FUNCTIONAL_LOGICAL_OR_HPP

#include <sprout/config.hpp>

namespace sprout {
	// 20.8.6 logical operations
	template<typename T>
	struct logical_or {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& x, T const& y) const {
			 return x || y;
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_LOGICAL_OR_HPP
