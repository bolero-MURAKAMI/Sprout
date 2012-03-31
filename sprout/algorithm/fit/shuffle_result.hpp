#ifndef SPROUT_ALGORITHM_FIT_SHUFFLE_RESULT_HPP
#define SPROUT_ALGORITHM_FIT_SHUFFLE_RESULT_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/fixed/shuffle_result.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename UniformRandomNumberGenerator, typename Shuffled>
			SPROUT_CONSTEXPR inline sprout::tuples::tuple<
				typename sprout::fit::result_of::algorithm<Container>::type,
				typename std::decay<UniformRandomNumberGenerator>::type
			> shuffle_result_impl_1(
				Shuffled const& shuffled,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				typedef sprout::tuples::tuple<
					typename sprout::fit::result_of::algorithm<Container>::type,
					typename std::decay<UniformRandomNumberGenerator>::type
				> result_type;
				return result_type(
					sprout::sub_copy(
						sprout::get_internal(sprout::tuples::get<0>(shuffled)),
						offset,
						offset + sprout::size(sprout::tuples::get<0>(shuffled))
						),
					sprout::tuples::get<1>(shuffled)
					);
			}
			template<typename Container, typename UniformRandomNumberGenerator>
			SPROUT_CONSTEXPR inline sprout::tuples::tuple<
				typename sprout::fit::result_of::algorithm<Container>::type,
				typename std::decay<UniformRandomNumberGenerator>::type
			> shuffle_result_impl(
				Container const& cont,
				UniformRandomNumberGenerator&& g,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::fit::detail::shuffle_result_impl_1<Container, UniformRandomNumberGenerator>(
					sprout::fixed::shuffle_result(cont, sprout::forward<UniformRandomNumberGenerator>(g)),
					offset
					);
			}
		}	// namespace detail
		//
		// shuffle_result
		//
		template<typename Container, typename UniformRandomNumberGenerator>
		SPROUT_CONSTEXPR inline sprout::tuples::tuple<
			typename sprout::fit::result_of::algorithm<Container>::type,
			typename std::decay<UniformRandomNumberGenerator>::type
		> shuffle_result(
			Container const& cont,
			UniformRandomNumberGenerator&& g
			)
		{
			return sprout::fit::detail::shuffle_result_impl(
				cont,
				sprout::forward<UniformRandomNumberGenerator>(g),
				sprout::internal_begin_offset(cont)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_SHUFFLE_RESULT_HPP
