#ifndef SPROUT_FIXED_CONTAINER_CONST_REFERENCE_HPP
#define SPROUT_FIXED_CONTAINER_CONST_REFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// fixed_const_reference
	//
	template<typename Container>
	struct fixed_const_reference {
	public:
		typedef typename sprout::fixed_container_traits<Container>::const_reference type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_CONST_REFERENCE_HPP
