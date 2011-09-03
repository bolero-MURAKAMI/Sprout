#ifndef SPROUT_FIXED_CONTAINER_FIXED_SIZE_HPP
#define SPROUT_FIXED_CONTAINER_FIXED_SIZE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// fixed_size
	//
	template<typename Container>
	struct fixed_size {
	public:
		typedef typename sprout::fixed_container_traits<Container>::size_type value
			= sprout::fixed_container_traits<Container>::fixed_size
			;
		typedef std::integral_constant<typename sprout::fixed_container_traits<Container>::size_type, value> type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_FIXED_SIZE_HPP
