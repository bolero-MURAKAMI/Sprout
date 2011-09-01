#ifndef SPROUT_ALGORITHM_OUTFIT_COPY_N_HPP
#define SPROUT_ALGORITHM_OUTFIT_COPY_N_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/copy_n.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Iterator, typename Size, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> copy_n_impl(
				Iterator first,
				Size n,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::copy_n(first, n, result),
					offset,
					offset + sprout::size(result)
					);
			}
		}	// namespace detail
		//
		// copy_n
		//
		template<typename Iterator, typename Size, typename Result>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> copy_n(
			Iterator first,
			Size n,
			Result const& result
			)
		{
			return sprout::outfit::detail::copy_n_impl(first, n, result, sprout::fixed_begin_offset(result));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_COPY_N_HPP
