#ifndef SPROUT_ALGORITHM_FIT_SORT_HEAP_HPP
#define SPROUT_ALGORITHM_FIT_SORT_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/sort_heap.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type sort_heap_impl(
				Container const& cont,
				Compare comp,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::sort_heap(cont, comp)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// sort_heap
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type sort_heap(
			Container const& cont,
			Compare comp
			)
		{
			return sprout::fit::detail::sort_heap_impl(cont, comp, sprout::internal_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type sort_heap_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::sort_heap(cont)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// sort_heap
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type sort_heap(
			Container const& cont
			)
		{
			return sprout::fit::detail::sort_heap_impl(cont, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_SORT_HEAP_HPP
