#ifndef SPROUT_CONTAINER_FIXED_SIZE_HPP
#define SPROUT_CONTAINER_FIXED_SIZE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// fixed_size
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
	fixed_size() {
		return sprout::container_traits<Container>::fixed_size();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_FIXED_SIZE_HPP
