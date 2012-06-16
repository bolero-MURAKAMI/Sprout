#ifndef SPROUT_CONTAINER_REBIND_SIZE_HPP
#define SPROUT_CONTAINER_REBIND_SIZE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_transform_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// rebind_size
		//
		template<typename Container, typename sprout::container_traits<Container>::size_type Size>
		struct rebind_size
			: public sprout::container_transform_traits<Container>::template rebind_size<Size>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_REBIND_SIZE_HPP
