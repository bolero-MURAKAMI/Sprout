#ifndef SPROUT_ALGORITHM_INFIT_REMOVE_COPY_HPP
#define SPROUT_ALGORITHM_INFIT_REMOVE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/remove_copy.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace infit {
		namespace detail {
			template<typename Iterator, typename Result, typename T>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> remove_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				T const& value,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::remove_copy(first, last, result, value),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last) - NS_SSCRISK_CEL_OR_SPROUT_DETAIL::count(first, last, value), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// remove_copy
		//
		template<typename Iterator, typename Result, typename T>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> remove_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			T const& value
			)
		{
			return sprout::infit::detail::remove_copy_impl(first, last, result, value, sprout::fixed_begin_offset(result));
		}
	}	// namespace infit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INFIT_REMOVE_COPY_HPP
