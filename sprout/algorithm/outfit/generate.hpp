#ifndef SPROUT_ALGORITHM_OUTFIT_GENERATE_HPP
#define SPROUT_ALGORITHM_OUTFIT_GENERATE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/generate.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Container, typename Generator, typename... Inits>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> generate_impl(
				Container const& cont,
				Generator gen,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				Inits const&... inits
				)
			{
				return sprout::sub_copy(
					sprout::fixed::generate(cont, gen, inits...),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// generate
		//
		template<typename Container, typename Generator, typename... Inits>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> generate(
			Container const& cont,
			Generator gen,
			Inits const&... inits
			)
		{
			return sprout::outfit::detail::generate_impl(cont, gen, sprout::fixed_begin_offset(cont), inits...);
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_GENERATE_HPP
