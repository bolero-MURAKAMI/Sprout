#ifndef SPROUT_FIXED_CONTAINER_POINTER_HPP
#define SPROUT_FIXED_CONTAINER_POINTER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/detail/if.hpp>

namespace sprout {
	//
	// fixed_pointer
	//
	template<typename Container>
	struct fixed_pointer {
	public:
		typedef typename sprout::detail::if_c<
			std::is_const<Container>::value,
			typename sprout::fixed_container_traits<Container>::const_pointer,
			typename sprout::fixed_container_traits<Container>::pointer
		>::type type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_POINTER_HPP
