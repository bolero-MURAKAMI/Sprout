#ifndef SPROUT_FIXED_CONTAINER_MUTABLE_ITERATOR_HPP
#define SPROUT_FIXED_CONTAINER_MUTABLE_ITERATOR_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// fixed_mutable_iterator
	//
	template<typename Container>
	struct fixed_mutable_iterator {
	public:
		typedef typename sprout::fixed_container_traits<Container>::iterator type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_MUTABLE_ITERATOR_HPP
