#ifndef SPROUT_FIXED_CONTAINER_SIZE_HPP
#define SPROUT_FIXED_CONTAINER_SIZE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/begin.hpp>
#include <sprout/fixed_container/end.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	//
	// size
	//
	template<typename Range>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<Range>::difference_type size(Range const& range) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(range), sprout::end(range));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_SIZE_HPP
