#ifndef SPROUT_FUNCTIONAL_BINARY_FUNCTION_HPP
#define SPROUT_FUNCTIONAL_BINARY_FUNCTION_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// binary_function
	//
	template<typename Arg1, typename Arg2, typename Result>
	struct binary_function {
	public:
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BINARY_FUNCTION_HPP
