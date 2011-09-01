#ifndef SPROUT_ALGORITHM_FIXED_GENERATE_N_HPP
#define SPROUT_ALGORITHM_FIXED_GENERATE_N_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/algorithm/fixed/generate.hpp>

namespace sprout {
	namespace fixed {
		//
		// generate_n
		//
		template<typename Container, typename Size, typename Generator, typename... Inits>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::fixed_container_type generate_n(
			Container const& cont,
			Size n,
			Generator gen,
			Inits const&... inits
			)
		{
			return sprout::fixed::detail::generate_impl(cont, gen, n, inits...);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_GENERATE_N_HPP
