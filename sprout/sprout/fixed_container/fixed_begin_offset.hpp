#ifndef SPROUT_FIXED_CONTAINER_FIXED_BEGIN_OFFSET_HPP
#define SPROUT_FIXED_CONTAINER_FIXED_BEGIN_OFFSET_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/begin.hpp>
#include <sprout/fixed_container/fixed_begin.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	//
	// fixed_begin_offset
	//
	template<typename Range>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<Range>::difference_type fixed_begin_offset(Range const& range) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(range), sprout::begin(range));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_FIXED_BEGIN_OFFSET_HPP
