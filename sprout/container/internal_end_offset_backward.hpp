#ifndef SPROUT_CONTAINER_INTERNAL_END_OFFSET_BACKWARD_HPP
#define SPROUT_CONTAINER_INTERNAL_END_OFFSET_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/end.hpp>
#include <sprout/container/internal_end.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	//
	// internal_end_offset_backward
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::difference_type
	internal_end_offset_backward(Container const& cont) {
		return sprout::distance(sprout::end(cont), sprout::internal_end(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_INTERNAL_END_OFFSET_BACKWARD_HPP
