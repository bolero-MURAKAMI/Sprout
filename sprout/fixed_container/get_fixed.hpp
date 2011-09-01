#ifndef SPROUT_FIXED_CONTAINER_GET_FIXED_HPP
#define SPROUT_FIXED_CONTAINER_GET_FIXED_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// get_fixed
	//
	template<typename Container>
	inline typename sprout::fixed_container_traits<Container>::fixed_container_type& get_fixed(Container& cont) {
		return get_fixed_functor<Container>()(cont);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::fixed_container_type const& get_fixed(Container const& cont) {
		return get_fixed_functor<Container>()(cont);
	}

	//
	// get_cfixed
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::fixed_container_type const& get_cfixed(Container const& cont) {
		return get_fixed_functor<Container>()(cont);
	}

	//
	// get_fixed_copy
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::fixed_container_type get_fixed_copy(Container const& cont) {
		return get_fixed_functor<Container>()(cont);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_GET_FIXED_HPP
