#ifndef SPROUT_ALGORITHM_FIT_GENERATE_N_HPP
#define SPROUT_ALGORITHM_FIT_GENERATE_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/generate_n.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Size, typename Generator, typename... Inits>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type generate_n_impl(
				Container const& cont,
				Size n,
				Generator gen,
				typename sprout::container_traits<Container>::difference_type offset,
				Inits const&... inits
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::generate_n(cont, n, gen, inits...)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n, sprout::size(cont))
					);
			}
		}	// namespace detail
		//
		// generate_n
		//
		template<typename Container, typename Size, typename Generator, typename... Inits>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type generate_n(
			Container const& cont,
			Size n,
			Generator gen,
			Inits const&... inits
			)
		{
			return sprout::fit::detail::generate_n_impl(cont, n, gen, sprout::internal_begin_offset(cont), inits...);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_GENERATE_N_HPP
