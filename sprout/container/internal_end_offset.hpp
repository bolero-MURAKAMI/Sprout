#ifndef SPROUT_CONTAINER_INTERNAL_END_OFFSET_HPP
#define SPROUT_CONTAINER_INTERNAL_END_OFFSET_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/end.hpp>
#include <sprout/container/internal_begin.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	//
	// internal_end_offset
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container>::difference_type internal_end_offset(Container const& cont) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::internal_begin(cont), sprout::end(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_INTERNAL_END_OFFSET_HPP
