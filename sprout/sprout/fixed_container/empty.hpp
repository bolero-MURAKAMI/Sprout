#ifndef SPROUT_FIXED_CONTAINER_EMPTY_HPP
#define SPROUT_FIXED_CONTAINER_EMPTY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/size.hpp>

namespace sprout {
	//
	// empty
	//
	template<typename Range>
	SPROUT_CONSTEXPR bool empty(Range const& range) {
		return sprout::size(range) == 0;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_EMPTY_HPP
