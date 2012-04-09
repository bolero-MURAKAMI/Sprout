#ifndef SPROUT_FUNCTIONAL_UNARY_FUNCTION_HPP
#define SPROUT_FUNCTIONAL_UNARY_FUNCTION_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// unary_function
	//
	template<typename Arg, typename Result>
	struct unary_function {
	public:
		typedef Arg argument_type;
		typedef Result result_type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_UNARY_FUNCTION_HPP
