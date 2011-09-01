#ifndef SPROUT_ALGORITHM_OUTFIT_REPLACE_COPY_HPP
#define SPROUT_ALGORITHM_OUTFIT_REPLACE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/replace_copy.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Iterator, typename Result, typename T>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> replace_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				T const& old_value,
				T const& new_value,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::replace_copy(first, last, result, old_value, new_value),
					offset,
					offset + sprout::size(result)
					);
			}
		}	// namespace detail
		//
		// replace_copy
		//
		template<typename Iterator, typename Result, typename T>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> replace_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			T const& old_value,
			T const& new_value
			)
		{
			return sprout::outfit::detail::replace_copy_impl(first, last, result, old_value, new_value, sprout::fixed_begin_offset(result));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_REPLACE_COPY_HPP
