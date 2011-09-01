#ifndef SPROUT_ALGORITHM_OUTFIT_COPY_IF_HPP
#define SPROUT_ALGORITHM_OUTFIT_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/copy_if.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Iterator, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> copy_if_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::copy_if(first, last, result, pred),
					offset,
					offset + sprout::size(result)
					);
			}
		}	// namespace detail
		//
		// copy_if
		//
		template<typename Iterator, typename Result, typename Predicate>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> copy_if(
			Iterator first,
			Iterator last,
			Result const& result,
			Predicate pred
			)
		{
			return sprout::outfit::detail::copy_if_impl(first, last, result, pred, sprout::fixed_begin_offset(result));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_COPY_IF_HPP
