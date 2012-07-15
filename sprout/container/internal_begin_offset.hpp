#ifndef SPROUT_CONTAINER_INTERNAL_BEGIN_OFFSET_HPP
#define SPROUT_CONTAINER_INTERNAL_BEGIN_OFFSET_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/container/internal_begin.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// internal_begin_offset
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::difference_type
	internal_begin_offset(Container const& cont) {
		return NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::internal_begin(cont), sprout::begin(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_INTERNAL_BEGIN_OFFSET_HPP
