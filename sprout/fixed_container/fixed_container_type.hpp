#ifndef SPROUT_FIXED_CONTAINER_FIXED_CONTAINER_TYPE_HPP
#define SPROUT_FIXED_CONTAINER_FIXED_CONTAINER_TYPE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// fixed_container_type
	//
	template<typename Container>
	struct fixed_container_type {
	public:
		typedef typename sprout::fixed_container_traits<Container>::fixed_container_type type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_FIXED_CONTAINER_TYPE_HPP