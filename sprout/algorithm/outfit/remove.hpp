#ifndef SPROUT_ALGORITHM_OUTFIT_REMOVE_HPP
#define SPROUT_ALGORITHM_OUTFIT_REMOVE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/remove.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Container, typename T>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> remove_impl(
				Container const& cont,
				T const& value,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::remove(cont, value),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// remove
		//
		template<typename Container, typename T>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> remove(
			Container const& cont,
			T const& value
			)
		{
			return sprout::outfit::detail::remove_impl(cont, value, sprout::fixed_begin_offset(cont));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_REMOVE_HPP
