#ifndef SPROUT_CONTAINER_SIZE_HPP
#define SPROUT_CONTAINER_SIZE_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/container/end.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	//
	// size
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::difference_type
	size(Container const& cont) {
		return sprout::distance(sprout::begin(cont), sprout::end(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_SIZE_HPP
