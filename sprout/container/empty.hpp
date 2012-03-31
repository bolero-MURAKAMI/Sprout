#ifndef SPROUT_CONTAINER_EMPTY_HPP
#define SPROUT_CONTAINER_EMPTY_HPP

#include <sprout/config.hpp>
#include <sprout/container/size.hpp>

namespace sprout {
	//
	// empty
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline bool empty(Container const& cont) {
		return sprout::size(cont) == 0;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_EMPTY_HPP
