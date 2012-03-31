#ifndef SPROUT_CONTAINER_SIZE_TYPE_HPP
#define SPROUT_CONTAINER_SIZE_TYPE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// size_type
		//
		template<typename Container>
		struct size_type {
		public:
			typedef typename sprout::container_traits<Container>::size_type type;
		};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_SIZE_TYPE_HPP
