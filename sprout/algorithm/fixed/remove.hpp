#ifndef SPROUT_ALGORITHM_FIXED_REMOVE_HPP
#define SPROUT_ALGORITHM_FIXED_REMOVE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/remove_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// remove
		//
		template<typename Container, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::fixed_container_type remove(
			Container const& cont,
			T const& value
			)
		{
			return sprout::fixed::remove_copy(sprout::begin(cont), sprout::end(cont), cont, value);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REMOVE_HPP
