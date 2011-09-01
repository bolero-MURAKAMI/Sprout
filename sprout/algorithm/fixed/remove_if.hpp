#ifndef SPROUT_ALGORITHM_FIXED_REMOVE_IF_HPP
#define SPROUT_ALGORITHM_FIXED_REMOVE_IF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/remove_copy_if.hpp>

namespace sprout {
	namespace fixed {
		//
		// remove_if
		//
		template<typename Container, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::fixed_container_type remove_if(
			Container const& cont,
			Predicate pred
			)
		{
			return sprout::fixed::remove_copy_if(sprout::begin(cont), sprout::end(cont), cont, pred);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REMOVE_IF_HPP
