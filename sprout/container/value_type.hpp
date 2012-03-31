#ifndef SPROUT_CONTAINER_VALUE_TYPE_HPP
#define SPROUT_CONTAINER_VALUE_TYPE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// value_type
		//
		template<typename Container>
		struct value_type {
		public:
			typedef typename sprout::container_traits<Container>::value_type type;
		};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_VALUE_TYPE_HPP
