#ifndef SPROUT_FIXED_CONTAINER_CLONE_HPP
#define SPROUT_FIXED_CONTAINER_CLONE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// clone
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<
		typename std::remove_reference<Container>::type
	>::clone_type clone(Container&& cont) {
		typedef typename std::decay<Container>::type container_type;
		return sprout::clone_functor<container_type>().template operator()(sprout::forward<Container>(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_CLONE_HPP
