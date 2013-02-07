#ifndef SPROUT_ALGORITHM_FIT_INPLACE_MERGE_HPP
#define SPROUT_ALGORITHM_FIT_INPLACE_MERGE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/inplace_merge.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
			inplace_merge_impl(
				Container const& cont, typename sprout::container_traits<Container>::const_iterator middle, Compare comp,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::inplace_merge(cont, middle, comp)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// inplace_merge
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
		inplace_merge(Container const& cont, typename sprout::container_traits<Container>::const_iterator middle, Compare comp) {
			return sprout::fit::detail::inplace_merge_impl(cont, middle, comp, sprout::internal_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
			inplace_merge_impl(
				Container const& cont, typename sprout::container_traits<Container>::const_iterator middle,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::inplace_merge(cont, middle)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// inplace_merge
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
		inplace_merge(Container const& cont, typename sprout::container_traits<Container>::const_iterator middle) {
			return sprout::fit::detail::inplace_merge_impl(cont, middle, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_INPLACE_MERGE_HPP
