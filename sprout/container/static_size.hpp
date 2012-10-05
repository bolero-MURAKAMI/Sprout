#ifndef SPROUT_CONTAINER_STATIC_SIZE_HPP
#define SPROUT_CONTAINER_STATIC_SIZE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// static_size
		//
		template<typename Container>
		struct static_size
			: public std::integral_constant<
				typename sprout::container_traits<Container>::size_type,
				sprout::container_traits<Container>::static_size
			>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_STATIC_SIZE_HPP
