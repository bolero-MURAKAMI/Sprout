#ifndef SPROUT_ALGORITHM_FIT_UNFOLD_HPP
#define SPROUT_ALGORITHM_FIT_UNFOLD_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/unfold.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Generator, typename Init>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type unfold_impl(
				Container const& cont,
				Generator const& gen,
				typename sprout::container_traits<Container>::difference_type offset,
				Init const& init
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::unfold(cont, gen, init)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// unfold
		//
		template<typename Container, typename Generator, typename Init>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type unfold(
			Container const& cont,
			Generator const& gen,
			Init const& init
			)
		{
			return sprout::fit::detail::unfold_impl(cont, gen, sprout::internal_begin_offset(cont), init);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_UNFOLD_HPP
