#ifndef SPROUT_FIXED_CONTAINER_CONST_ITERATOR_HPP
#define SPROUT_FIXED_CONTAINER_CONST_ITERATOR_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// fixed_const_iterator
	//
	template<typename Container>
	struct fixed_const_iterator {
	public:
		typedef typename sprout::fixed_container_traits<Container>::const_iterator type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_CONST_ITERATOR_HPP
