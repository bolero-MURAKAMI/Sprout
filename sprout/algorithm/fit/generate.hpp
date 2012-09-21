#ifndef SPROUT_ALGORITHM_FIT_GENERATE_HPP
#define SPROUT_ALGORITHM_FIT_GENERATE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/generate.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Generator>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type generate_impl(
				Container const& cont,
				Generator gen,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::generate(cont, gen)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// generate
		//
		template<typename Container, typename Generator>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type generate(
			Container const& cont,
			Generator gen
			)
		{
			return sprout::fit::detail::generate_impl(cont, gen, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_GENERATE_HPP
