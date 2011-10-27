#ifndef SPROUT_FIXED_CONTAINER_FIXED_BEGIN_OFFSET_BACKWARD_HPP
#define SPROUT_FIXED_CONTAINER_FIXED_BEGIN_OFFSET_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/begin.hpp>
#include <sprout/fixed_container/fixed_end.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	//
	// fixed_begin_offset_backward
	//
	template<typename Range>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<Range>::difference_type fixed_begin_offset_backward(Range const& range) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(range), sprout::fixed_end(range));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_FIXED_BEGIN_OFFSET_BACKWARD_HPP
