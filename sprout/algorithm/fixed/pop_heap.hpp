#ifndef SPROUT_ALGORITHM_FIXED_POP_HEAP_HPP
#define SPROUT_ALGORITHM_FIXED_POP_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type pop_heap_impl(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::difference_type size,
				typename sprout::fixed_container_traits<Container>::difference_type n = 0,
				typename sprout::fixed_container_traits<Container>::difference_type l = 1,
				typename sprout::fixed_container_traits<Container>::difference_type r = 2
				)
			{
				return r < size && comp(*sprout::next(sprout::fixed_begin(cont), offset + l), *sprout::next(sprout::fixed_begin(cont), offset + r))
					? comp(*sprout::next(sprout::fixed_begin(cont), offset + n), *sprout::next(sprout::fixed_begin(cont), offset + r))
						? sprout::fixed::detail::pop_heap_impl(
							sprout::fixed::swap_element(
								cont,
								sprout::next(sprout::fixed_begin(cont), offset + n),
								sprout::next(sprout::fixed_begin(cont), offset + r)
								),
							comp,
							offset,
							size,
							r,
							r * 2 + 1,
							r * 2 + 2
							)
						: sprout::clone(cont)
					: l < size
						? comp(*sprout::next(sprout::fixed_begin(cont), offset + n), *sprout::next(sprout::fixed_begin(cont), offset + l))
							? sprout::fixed::detail::pop_heap_impl(
								sprout::fixed::swap_element(
									cont,
									sprout::next(sprout::fixed_begin(cont), offset + n),
									sprout::next(sprout::fixed_begin(cont), offset + l)
									),
								comp,
								offset,
								size,
								l,
								l * 2 + 1,
								l * 2 + 2
								)
							: sprout::clone(cont)
						: sprout::clone(cont)
					;
			}
		}	// namespace detail
		//
		// pop_heap
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type pop_heap(
			Container const& cont,
			Compare comp
			)
		{
			return sprout::fixed::detail::pop_heap_impl(
				sprout::fixed::swap_element(cont, sprout::begin(cont), sprout::end(cont) - 1),
				comp,
				sprout::fixed_begin_offset(cont),
				sprout::size(cont) - 1
				);
		}
		//
		// pop_heap
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type pop_heap(
			Container const& cont
			)
		{
			return sprout::fixed::detail::pop_heap_impl(
				sprout::fixed::swap_element(cont, sprout::begin(cont), sprout::end(cont) - 1),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::fixed_container_traits<Container>::value_type>(),
				sprout::fixed_begin_offset(cont),
				sprout::size(cont) - 1
				);
		}
	}	// namespace fixed

	using sprout::fixed::pop_heap;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_POP_HEAP_HPP
