#ifndef SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_COPY_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Iterator, typename Result, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type swap_element_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				sprout::index_tuple<Indexes...>,
				Iterator pos1,
				Iterator pos2,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				typename sprout::fixed_container_traits<Result>::size_type size,
				typename sprout::fixed_container_traits<Result>::size_type input_size
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? first + Indexes - offset == pos1
							? *pos2
							: first + Indexes - offset == pos2
							? *pos1
							: *(first + Indexes - offset)
						: *(sprout::fixed_begin(result) + Indexes)
						)...
					};
			}
		}	// namespace detail
		//
		// swap_element_copy
		//
		template<typename Iterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type swap_element_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			Iterator pos1,
			Iterator pos2
			)
		{
			return sprout::fixed::detail::swap_element_copy_impl(
				first,
				last,
				result,
				typename sprout::index_range<0, sprout::fixed_container_traits<Result>::fixed_size>::type(),
				pos1,
				pos2,
				sprout::fixed_begin_offset(result),
				sprout::size(result),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last)
				);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_COPY_HPP
