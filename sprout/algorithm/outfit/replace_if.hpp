#ifndef SPROUT_ALGORITHM_OUTFIT_REPLACE_IF_HPP
#define SPROUT_ALGORITHM_OUTFIT_REPLACE_IF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/replace_if.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Container, typename T, typename Predicate>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> replace_if_impl(
				Container const& cont,
				Predicate pred,
				T const& new_value,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::replace_if(cont, pred, new_value),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// replace_if
		//
		template<typename Container, typename T, typename Predicate>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> replace_if(
			Container const& cont,
			Predicate pred,
			T const& new_value
			)
		{
			return sprout::outfit::detail::replace_if_impl(cont, pred, new_value, sprout::fixed_begin_offset(cont));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_REPLACE_IF_HPP
