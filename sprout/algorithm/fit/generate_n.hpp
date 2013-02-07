#ifndef SPROUT_ALGORITHM_FIT_GENERATE_N_HPP
#define SPROUT_ALGORITHM_FIT_GENERATE_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/generate_n.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Size, typename Generator>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
			generate_n_impl(
				Container const& cont, Size n, Generator const& gen,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::generate_n(cont, n, gen)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(n, sprout::size(cont))
					);
			}
		}	// namespace detail
		//
		// generate_n
		//
		template<typename Container, typename Size, typename Generator>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
		generate_n(Container const& cont, Size n, Generator const& gen) {
			return sprout::fit::detail::generate_n_impl(cont, n, gen, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_GENERATE_N_HPP
