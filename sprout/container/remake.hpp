#ifndef SPROUT_CONTAINER_REMAKE_HPP
#define SPROUT_CONTAINER_REMAKE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/container_construct_traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// remake
	//
	template<typename Container, typename Cont, typename... Args>
	inline SPROUT_CONSTEXPR typename sprout::container_construct_traits<Container>::copied_type remake(
		Cont&& cont,
		typename sprout::container_traits<Container>::difference_type size,
		Args&&... args
		)
	{
		return sprout::container_construct_traits<Container>::remake(
			sprout::forward<Cont>(cont),
			size,
			sprout::forward<Args>(args)...
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_REMAKE_HPP
