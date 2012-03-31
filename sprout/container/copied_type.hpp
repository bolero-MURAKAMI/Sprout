#ifndef SPROUT_CONTAINER_COPIED_TYPE_HPP
#define SPROUT_CONTAINER_COPIED_TYPE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_construct_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// copied_type
		//
		template<typename Container>
		struct copied_type {
		public:
			typedef typename sprout::container_construct_traits<Container>::copied_type type;
		};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_COPIED_TYPE_HPP
