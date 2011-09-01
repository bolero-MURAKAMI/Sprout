#ifndef SPROUT_FIXED_CONTAINER_FIXED_END_OFFSET_HPP
#define SPROUT_FIXED_CONTAINER_FIXED_END_OFFSET_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/end.hpp>
#include <sprout/fixed_container/fixed_begin.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	//
	// fixed_end_offset
	//
	template<typename Range>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<Range>::difference_type fixed_end_offset(Range const& range) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(range), sprout::end(range));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_FIXED_END_OFFSET_HPP
