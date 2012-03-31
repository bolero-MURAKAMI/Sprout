#ifndef SPROUT_CONTAINER_CONST_REFERENCE_HPP
#define SPROUT_CONTAINER_CONST_REFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// const_reference
		//
		template<typename Container>
		struct const_reference {
		public:
			typedef typename sprout::container_traits<Container>::const_reference type;
		};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONST_REFERENCE_HPP
