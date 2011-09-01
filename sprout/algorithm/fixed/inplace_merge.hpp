#ifndef SPROUT_ALGORITHM_FIXED_INPLACE_MERGE_HPP
#define SPROUT_ALGORITHM_FIXED_INPLACE_MERGE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/merge.hpp>

namespace sprout {
	namespace fixed {
		//
		// inplace_merge
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::fixed_container_type inplace_merge(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator middle,
			Compare comp
			)
		{
			return sprout::fixed::merge(
				sprout::begin(cont),
				middle,
				middle,
				sprout::end(cont),
				cont,
				comp
				);
		}
		//
		// inplace_merge
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::fixed_container_type inplace_merge(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator middle
			)
		{
			return sprout::fixed::merge(
				sprout::begin(cont),
				middle,
				middle,
				sprout::end(cont),
				cont
				);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_INPLACE_MERGE_HPP
