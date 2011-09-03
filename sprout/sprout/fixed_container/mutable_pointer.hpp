#ifndef SPROUT_FIXED_CONTAINER_MUTABLE_POINTER_HPP
#define SPROUT_FIXED_CONTAINER_MUTABLE_POINTER_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// fixed_mutable_pointer
	//
	template<typename Container>
	struct fixed_mutable_pointer {
	public:
		typedef typename sprout::fixed_container_traits<Container>::pointer type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_MUTABLE_POINTER_HPP
