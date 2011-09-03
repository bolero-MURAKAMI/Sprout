#ifndef SPROUT_FIXED_CONTAINER_CLONE_HPP
#define SPROUT_FIXED_CONTAINER_CLONE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// clone
	//
	template<typename Container>
	inline typename sprout::fixed_container_traits<Container>::clone_type clone(Container& cont) {
		return sprout::clone_functor<Container>().template operator()(cont);
	}
	template<typename Container, typename... Args>
	SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::clone_type clone(Container const& cont) {
		return sprout::clone_functor<Container>().template operator()(cont);
	}

	//
	// cclone
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::clone_type cclone(Container const& cont) {
		return sprout::clone_functor<Container>().template operator()(cont);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_CLONE_HPP
