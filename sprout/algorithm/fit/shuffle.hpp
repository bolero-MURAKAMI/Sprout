#ifndef SPROUT_ALGORITHM_FIT_SHUFFLE_HPP
#define SPROUT_ALGORITHM_FIT_SHUFFLE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/fixed/shuffle.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename UniformRandomNumberGenerator>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
			shuffle_impl(
				Container const& cont, UniformRandomNumberGenerator&& g,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::shuffle(cont, sprout::forward<UniformRandomNumberGenerator>(g))),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// shuffle
		//
		template<typename Container, typename UniformRandomNumberGenerator>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
		shuffle(Container const& cont, UniformRandomNumberGenerator&& g) {
			return sprout::fit::detail::shuffle_impl(
				cont, sprout::forward<UniformRandomNumberGenerator>(g),
				sprout::internal_begin_offset(cont)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_SHUFFLE_HPP
