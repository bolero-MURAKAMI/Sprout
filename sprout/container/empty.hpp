#ifndef SPROUT_CONTAINER_EMPTY_HPP
#define SPROUT_CONTAINER_EMPTY_HPP

#include <sprout/config.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/container/end.hpp>

namespace sprout {
	//
	// empty
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline bool empty(Container const& cont) {
		return sprout::begin(cont) == sprout::end(cont);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_EMPTY_HPP
