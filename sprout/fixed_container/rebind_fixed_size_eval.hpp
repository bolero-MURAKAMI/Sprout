#ifndef SPROUT_FIXED_CONTAINER_REBIND_FIXED_SIZE_EVAL_HPP
#define SPROUT_FIXED_CONTAINER_REBIND_FIXED_SIZE_EVAL_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// rebind_fixed_size_eval
	//
	template<typename Container, typename sprout::fixed_container_traits<Container>::size_type S>
	struct rebind_fixed_size_eval
		: public rebind_fixed_size<Container>::template apply<S>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_REBIND_FIXED_SIZE_EVAL_HPP
