#ifndef SPROUT_ALGORITHM_FIXED_ROTATE_HPP
#define SPROUT_ALGORITHM_FIXED_ROTATE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/rotate_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// rotate
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::fixed_container_type rotate(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator middle
			)
		{
			return sprout::fixed::rotate_copy(sprout::begin(cont), middle, sprout::end(cont), cont);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_ROTATE_HPP
