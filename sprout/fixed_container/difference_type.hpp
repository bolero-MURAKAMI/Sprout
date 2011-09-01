#ifndef SPROUT_FIXED_CONTAINER_DIFFERENCE_TYPE_HPP
#define SPROUT_FIXED_CONTAINER_DIFFERENCE_TYPE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// fixed_difference_type
	//
	template<typename Container>
	struct fixed_difference_type {
	public:
		typedef typename sprout::fixed_container_traits<Container>::difference_type type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_DIFFERENCE_TYPE_HPP
