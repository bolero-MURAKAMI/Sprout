#ifndef SPROUT_FIXED_CONTAINER_REMAKE_CLONE_HPP
#define SPROUT_FIXED_CONTAINER_REMAKE_CLONE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// remake_clone
	//
	template<typename Container, typename Other, typename... Args>
	inline typename sprout::fixed_container_traits<Container>::clone_type remake_clone(
		Other& other,
		typename sprout::fixed_container_traits<Container>::difference_type size,
		Args const&... args
		)
	{
		return sprout::remake_clone_functor<Container>().template operator()(other, size, args...);
	}
	template<typename Container, typename Other, typename... Args>
	SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::clone_type remake_clone(Other const& other, Args const&... args) {
		return sprout::remake_clone_functor<Container>().template operator()(other, args...);
	}

	//
	// remake_cclone
	//
	template<typename Container, typename Other, typename... Args>
	SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::clone_type remake_cclone(
		Other const& other,
		typename sprout::fixed_container_traits<Container>::difference_type size,
		Args const&... args
		)
	{
		return sprout::remake_clone_functor<Container>().template operator()(other, size, args...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_REMAKE_CLONE_HPP
