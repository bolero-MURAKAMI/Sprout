#ifndef SPROUT_FIXED_CONTAINER_GET_INTERNAL_HPP
#define SPROUT_FIXED_CONTAINER_GET_INTERNAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/sub_container_traits.hpp>
#include <sprout/container/internal.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// get_internal
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename sprout::containers::internal<Container>::type get_internal(Container&& cont) {
		typedef typename std::remove_reference<Container>::type container_type;
		return sprout::sub_container_traits<container_type>::get_internal(sprout::forward<Container>(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_GET_INTERNAL_HPP
