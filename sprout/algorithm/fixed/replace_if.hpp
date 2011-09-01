#ifndef SPROUT_ALGORITHM_FIXED_REPLACE_IF_HPP
#define SPROUT_ALGORITHM_FIXED_REPLACE_IF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/replace_copy_if.hpp>

namespace sprout {
	namespace fixed {
		//
		// replace_if
		//
		template<typename Container, typename T, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::fixed_container_type replace_if(
			Container const& cont,
			Predicate pred,
			T const& new_value
			)
		{
			return sprout::fixed::replace_copy_if(sprout::begin(cont), sprout::end(cont), cont, pred, new_value);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REPLACE_IF_HPP
