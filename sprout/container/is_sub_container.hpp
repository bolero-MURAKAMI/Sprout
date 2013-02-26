#ifndef SPROUT_CONTAINER_IS_SUB_CONTAINER_HPP
#define SPROUT_CONTAINER_IS_SUB_CONTAINER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/internal.hpp>

namespace sprout {
	namespace containers {
		//
		// is_sub_container
		//
		template<typename Container>
		struct is_sub_container
			: public std::integral_constant<
				bool,
				!std::is_same<typename sprout::containers::internal<Container>::type, Container&&>::value
			>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_IS_SUB_CONTAINER_HPP
