#ifndef SPROUT_CONTAINER_REFERENCE_HPP
#define SPROUT_CONTAINER_REFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// reference
		//
		template<typename Container>
		struct reference {
		public:
			typedef typename sprout::container_traits<Container>::reference type;
		};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_REFERENCE_HPP
