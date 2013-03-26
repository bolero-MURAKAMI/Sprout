#ifndef SPROUT_CONTAINER_INTERNAL_HPP
#define SPROUT_CONTAINER_INTERNAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/sub_container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// internal
		//
		template<typename Container>
		struct internal
			: public sprout::sub_container_traits<
				typename std::remove_reference<Container>::type
			>::template internal<Container>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_INTERNAL_HPP
