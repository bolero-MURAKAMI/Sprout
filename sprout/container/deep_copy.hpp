#ifndef SPROUT_CONTAINER_DEEP_COPY_HPP
#define SPROUT_CONTAINER_DEEP_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/container_construct_traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// deep_copy
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename sprout::container_construct_traits<
		typename std::remove_reference<Container>::type
	>::copied_type deep_copy(Container&& cont) {
		typedef typename std::remove_reference<Container>::type container_type;
		return sprout::container_construct_traits<container_type>::deep_copy(sprout::forward<Container>(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_DEEP_COPY_HPP
