#ifndef SPROUT_FIXED_CONTAINER_REFERENCE_HPP
#define SPROUT_FIXED_CONTAINER_REFERENCE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/detail/if.hpp>

namespace sprout {
	//
	// fixed_reference
	//
	template<typename Container>
	struct fixed_reference {
	public:
		typedef typename sprout::detail::if_c<
			std::is_const<Container>::value,
			typename sprout::fixed_container_traits<Container>::const_reference,
			typename sprout::fixed_container_traits<Container>::reference
		>::type type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_REFERENCE_HPP
