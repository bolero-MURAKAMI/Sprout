#ifndef SPROUT_FIXED_CONTAINER_MAKE_CLONE_HPP
#define SPROUT_FIXED_CONTAINER_MAKE_CLONE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// make_clone
	//
	template<typename Container, typename... Args>
	SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<
		typename std::remove_reference<Container>::type
	>::clone_type make_clone(Args&&... args) {
		typedef typename std::remove_reference<Container>::type container_type;
		return sprout::make_clone_functor<container_type>().template operator()(sprout::forward<Args>(args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_MAKE_CLONE_HPP
