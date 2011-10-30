#ifndef SPROUT_FIXED_CONTAINER_REMAKE_CLONE_HPP
#define SPROUT_FIXED_CONTAINER_REMAKE_CLONE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// remake_clone
	//
	template<typename Container, typename Other, typename... Args>
	SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<
		typename std::remove_reference<Container>::type
	>::clone_type remake_clone(
		Other&& other,
		typename sprout::fixed_container_traits<Container>::difference_type size,
		Args&&... args
		)
	{
		typedef typename std::remove_reference<Container>::type container_type;
		return sprout::remake_clone_functor<container_type>().template operator()(
			sprout::forward<Other>(other),
			size,
			sprout::forward<Args>(args)...
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_REMAKE_CLONE_HPP
