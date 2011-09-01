#ifndef SPROUT_ALGORITHM_OUTFIT_SWAP_ELEMENT_COPY_HPP
#define SPROUT_ALGORITHM_OUTFIT_SWAP_ELEMENT_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/swap_element_copy.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Iterator, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> swap_element_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				Iterator pos1,
				Iterator pos2,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::swap_element_copy(first, last, result, pos1, pos2),
					offset,
					offset + sprout::size(result)
					);
			}
		}	// namespace detail
		//
		// swap_element_copy
		//
		template<typename Iterator, typename Result>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> swap_element_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			Iterator pos1,
			Iterator pos2
			)
		{
			return sprout::outfit::detail::swap_element_copy_impl(first, last, result, pos1, pos2, sprout::fixed_begin_offset(result));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_SWAP_ELEMENT_COPY_HPP
