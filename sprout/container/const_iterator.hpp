#ifndef SPROUT_CONTAINER_CONST_ITERATOR_HPP
#define SPROUT_CONTAINER_CONST_ITERATOR_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// const_iterator
		//
		template<typename Container>
		struct const_iterator {
		public:
			typedef typename sprout::container_traits<Container>::const_iterator type;
		};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONST_ITERATOR_HPP
