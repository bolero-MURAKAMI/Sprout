#ifndef SPROUT_FIXED_CONTAINER_MAKE_CLONE_HPP
#define SPROUT_FIXED_CONTAINER_MAKE_CLONE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// make_clone
	//
	template<typename Container, typename... Args>
	SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::clone_type make_clone(Args const&... args) {
		return sprout::make_clone_functor<Container>().template operator()(args...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_MAKE_CLONE_HPP
