#ifndef SPROUT_ALGORITHM_FIT_UNFOLD_N_HPP
#define SPROUT_ALGORITHM_FIT_UNFOLD_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/unfold_n.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Size, typename Generator, typename... Inits>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type unfold_n_impl(
				Container const& cont,
				Size n,
				Generator gen,
				typename sprout::container_traits<Container>::difference_type offset,
				Inits const&... inits
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::unfold_n(cont, n, gen, inits...)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(n, sprout::size(cont))
					);
			}
		}	// namespace detail
		//
		// unfold_n
		//
		template<typename Container, typename Size, typename Generator, typename... Inits>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type unfold_n(
			Container const& cont,
			Size n,
			Generator gen,
			Inits const&... inits
			)
		{
			return sprout::fit::detail::unfold_n_impl(cont, n, gen, sprout::internal_begin_offset(cont), inits...);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_UNFOLD_N_HPP
