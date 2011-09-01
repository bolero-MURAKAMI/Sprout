#ifndef SPROUT_ALGORITHM_OUTFIT_COPY_BACKWARD_HPP
#define SPROUT_ALGORITHM_OUTFIT_COPY_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/copy_backward.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Iterator, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> copy_backward_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::copy_backward(first, last, result),
					offset,
					offset + sprout::size(result)
					);
			}
		}	// namespace detail
		//
		// copy_backward
		//
		template<typename Iterator, typename Result>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> copy_backward(
			Iterator first,
			Iterator last,
			Result const& result
			)
		{
			return sprout::outfit::detail::copy_backward_impl(first, last, result, sprout::fixed_begin_offset(result));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_COPY_BACKWARD_HPP
