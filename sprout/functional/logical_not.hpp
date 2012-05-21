#ifndef SPROUT_FUNCTIONAL_LOGICAL_NOT_HPP
#define SPROUT_FUNCTIONAL_LOGICAL_NOT_HPP

#include <sprout/config.hpp>

namespace sprout {
	// 20.8.6 logical operations
	template<typename T>
	struct logical_not {
	public:
		typedef T argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& x) const {
				return !x;
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_LOGICAL_NOT_HPP
