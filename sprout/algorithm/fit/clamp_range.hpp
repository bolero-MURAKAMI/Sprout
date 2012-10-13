#ifndef SPROUT_ALGORITHM_FIT_CLAMP_RANGE_HPP
#define SPROUT_ALGORITHM_FIT_CLAMP_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/clamp_range.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
			clamp_range_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::value_type const& low,
				typename sprout::container_traits<Container>::value_type const& high,
				Compare comp,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::clamp_range(cont, low, high, comp)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// clamp_range
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
		clamp_range(
			Container const& cont,
			typename sprout::container_traits<Container>::value_type const& low,
			typename sprout::container_traits<Container>::value_type const& high,
			Compare comp
			)
		{
			return sprout::fit::detail::clamp_range_impl(cont, low, high, comp, sprout::internal_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
			clamp_range_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::value_type const& low,
				typename sprout::container_traits<Container>::value_type const& high,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::clamp_range(cont, low, high)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// clamp_range
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
		clamp_range(
			Container const& cont,
			typename sprout::container_traits<Container>::value_type const& low,
			typename sprout::container_traits<Container>::value_type const& high
			)
		{
			return sprout::fit::detail::clamp_range_impl(cont, low, high, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_CLAMP_RANGE_HPP
