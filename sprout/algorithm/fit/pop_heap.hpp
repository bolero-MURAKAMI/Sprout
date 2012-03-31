#ifndef SPROUT_ALGORITHM_FIT_POP_HEAP_HPP
#define SPROUT_ALGORITHM_FIT_POP_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/pop_heap.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type pop_heap_impl(
				Container const& cont,
				Compare comp,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::pop_heap(cont, comp)),
					offset,
					offset + sprout::size(cont) - 1
					);
			}
		}	// namespace detail
		//
		// pop_heap
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type pop_heap(
			Container const& cont,
			Compare comp
			)
		{
			return sprout::fit::detail::pop_heap_impl(cont, comp, sprout::internal_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type pop_heap_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::pop_heap(cont)),
					offset,
					offset + sprout::size(cont) - 1
					);
			}
		}	// namespace detail
		//
		// pop_heap
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type pop_heap(
			Container const& cont
			)
		{
			return sprout::fit::detail::pop_heap_impl(cont, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_POP_HEAP_HPP
