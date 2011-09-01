#ifndef SPROUT_ALGORITHM_OUTFIT_ROTATE_COPY_HPP
#define SPROUT_ALGORITHM_OUTFIT_ROTATE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/rotate_copy.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Iterator, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> rotate_copy_impl(
				Iterator first,
				Iterator middle,
				Iterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::rotate_copy(first, middle, last, result),
					offset,
					offset + sprout::size(result)
					);
			}
		}	// namespace detail
		//
		// rotate_copy
		//
		template<typename Iterator, typename Result>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> rotate_copy(
			Iterator first,
			Iterator middle,
			Iterator last,
			Result const& result
			)
		{
			return sprout::outfit::detail::rotate_copy_impl(first, middle, last, result, sprout::fixed_begin_offset(result));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_ROTATE_COPY_HPP
