#ifndef SPROUT_CONTAINER_MAKE_HPP
#define SPROUT_CONTAINER_MAKE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_construct_traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// make
	//
	template<typename Container, typename... Args>
	SPROUT_CONSTEXPR inline typename sprout::container_construct_traits<Container>::copied_type make(Args&&... args) {
		return sprout::container_construct_traits<Container>::make(sprout::forward<Args>(args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_MAKE_HPP
