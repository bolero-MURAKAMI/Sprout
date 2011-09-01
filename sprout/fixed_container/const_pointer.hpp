#ifndef SPROUT_FIXED_CONTAINER_CONST_POINTER_HPP
#define SPROUT_FIXED_CONTAINER_CONST_POINTER_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// fixed_const_pointer
	//
	template<typename Container>
	struct fixed_const_pointer {
	public:
		typedef typename sprout::fixed_container_traits<Container>::const_pointer type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_CONST_POINTER_HPP
