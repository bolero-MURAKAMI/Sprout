#ifndef SPROUT_CONTAINER_CONST_POINTER_HPP
#define SPROUT_CONTAINER_CONST_POINTER_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// const_pointer
		//
		template<typename Container>
		struct const_pointer {
		public:
			typedef typename sprout::container_traits<Container>::const_pointer type;
		};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONST_POINTER_HPP
