#ifndef SPROUT_ALGORITHM_OUTFIT_GENERATE_N_HPP
#define SPROUT_ALGORITHM_OUTFIT_GENERATE_N_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/generate_n.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Container, typename Size, typename Generator, typename... Inits>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> generate_n_impl(
				Container const& cont,
				Size n,
				Generator gen,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				Inits const&... inits
				)
			{
				return sprout::sub_copy(
					sprout::fixed::generate_n(cont, n, gen, inits...),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// generate_n
		//
		template<typename Container, typename Size, typename Generator, typename... Inits>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> generate_n(
			Container const& cont,
			Size n,
			Generator gen,
			Inits const&... inits
			)
		{
			return sprout::outfit::detail::generate_n_impl(cont, n, gen, sprout::fixed_begin_offset(cont), inits...);
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_GENERATE_N_HPP
