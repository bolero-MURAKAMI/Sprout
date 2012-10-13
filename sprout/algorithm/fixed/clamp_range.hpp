#ifndef SPROUT_ALGORITHM_FIXED_CLAMP_RANGE_HPP
#define SPROUT_ALGORITHM_FIXED_CLAMP_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/clamp_range_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// clamp_range
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		clamp_range(
			Container const& cont,
			typename sprout::container_traits<Container>::value_type const& low,
			typename sprout::container_traits<Container>::value_type const& high,
			Compare comp
			)
		{
			return sprout::fixed::clamp_range_copy(sprout::begin(cont), sprout::end(cont), cont, low, high, comp);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		clamp_range(
			Container const& cont,
			typename sprout::container_traits<Container>::value_type const& low,
			typename sprout::container_traits<Container>::value_type const& high
			)
		{
			return sprout::fixed::clamp_range_copy(sprout::begin(cont), sprout::end(cont), cont, low, high);
		}
	}	// namespace fixed

	using sprout::fixed::clamp_range;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_CLAMP_RANGE_HPP
