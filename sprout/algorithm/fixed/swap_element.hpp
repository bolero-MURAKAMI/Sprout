#ifndef SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_HPP
#define SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// swap_element
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type swap_element(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator pos1,
			typename sprout::fixed_container_traits<Container>::const_iterator pos2
			)
		{
			return sprout::fixed::swap_element_copy(sprout::begin(cont), sprout::end(cont), cont, pos1, pos2);
		}
	}	// namespace fixed

	using sprout::fixed::swap_element;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_HPP
