#ifndef SPROUT_FIXED_CONTAINER_VALUE_TYPE_HPP
#define SPROUT_FIXED_CONTAINER_VALUE_TYPE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// fixed_value_type
	//
	template<typename Container>
	struct fixed_value_type {
	public:
		typedef typename sprout::fixed_container_traits<Container>::value_type type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_VALUE_TYPE_HPP
