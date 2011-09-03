#ifndef SPROUT_FIXED_CONTAINER_MUTABLE_REFERENCE_HPP
#define SPROUT_FIXED_CONTAINER_MUTABLE_REFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// fixed_mutable_reference
	//
	template<typename Container>
	struct fixed_mutable_reference {
	public:
		typedef typename sprout::fixed_container_traits<Container>::reference type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_MUTABLE_REFERENCE_HPP
