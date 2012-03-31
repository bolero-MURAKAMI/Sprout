#ifndef SPROUT_CONTAINER_POINTER_HPP
#define SPROUT_CONTAINER_POINTER_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// pointer
		//
		template<typename Container>
		struct pointer {
		public:
			typedef typename sprout::container_traits<Container>::pointer type;
		};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_POINTER_HPP
