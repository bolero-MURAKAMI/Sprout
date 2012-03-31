#ifndef SPROUT_CONTAINER_SIZE_HPP
#define SPROUT_CONTAINER_SIZE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/container/end.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	//
	// size
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename sprout::container_traits<Container>::difference_type size(Container const& cont) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), sprout::end(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_SIZE_HPP
