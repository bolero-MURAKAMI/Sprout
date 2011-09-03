#ifndef SPROUT_ALGORITHM_FIXED_REVERSE_HPP
#define SPROUT_ALGORITHM_FIXED_REVERSE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/reverse_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// reverse
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type reverse(
			Container const& cont
			)
		{
			return sprout::fixed::reverse_copy(sprout::begin(cont), sprout::end(cont), cont);
		}
	}	// namespace fixed

	using sprout::fixed::reverse;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REVERSE_HPP
