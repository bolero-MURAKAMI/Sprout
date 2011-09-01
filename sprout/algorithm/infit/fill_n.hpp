#ifndef SPROUT_ALGORITHM_INFIT_FILL_N_HPP
#define SPROUT_ALGORITHM_INFIT_FILL_N_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/fill_n.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace infit {
		namespace detail {
			template<typename Container, typename Size, typename T>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> fill_n_impl(
				Container const& cont,
				Size n,
				T const& value,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::fill_n(cont, n, value),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n, sprout::size(cont))
					);
			}
		}	// namespace detail
		//
		// fill_n
		//
		template<typename Container, typename Size, typename T>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> fill_n(
			Container const& cont,
			Size n,
			T const& value
			)
		{
			return sprout::infit::detail::fill_n_impl(cont, n, value, sprout::fixed_begin_offset(cont));
		}
	}	// namespace infit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INFIT_FILL_N_HPP
