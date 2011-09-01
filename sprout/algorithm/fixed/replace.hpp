#ifndef SPROUT_ALGORITHM_FIXED_REPLACE_HPP
#define SPROUT_ALGORITHM_FIXED_REPLACE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/replace_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// replace
		//
		template<typename Container, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::fixed_container_type replace(
			Container const& cont,
			T const& old_value,
			T const& new_value
			)
		{
			return sprout::fixed::replace_copy(sprout::begin(cont), sprout::end(cont), cont, old_value, new_value);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REPLACE_HPP
