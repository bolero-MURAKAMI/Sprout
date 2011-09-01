#ifndef SPROUT_ALGORITHM_INFIT_UNIQUE_HPP
#define SPROUT_ALGORITHM_INFIT_UNIQUE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/unique.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/detail/overlap_count.hpp>

namespace sprout {
	namespace infit {
		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> unique_impl(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::unique(cont),
					offset,
					offset + sprout::size(cont) - sprout::detail::overlap_count(sprout::begin(cont), sprout::end(cont))
					);
			}
		}	// namespace detail
		//
		// unique
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> unique(
			Container const& cont
			)
		{
			return sprout::infit::detail::unique_impl(cont, sprout::fixed_begin_offset(cont));
		}

		namespace detail {
			template<typename Container, typename BinaryPredicate>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> unique_impl(
				Container const& cont,
				BinaryPredicate pred,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::unique(cont, pred),
					offset,
					offset + sprout::size(cont) - sprout::detail::overlap_count(sprout::begin(cont), sprout::end(cont), pred)
					);
			}
		}	// namespace detail
		//
		// unique
		//
		template<typename Container, typename BinaryPredicate>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> unique(
			Container const& cont,
			BinaryPredicate pred
			)
		{
			return sprout::infit::detail::unique_impl(cont, pred, sprout::fixed_begin_offset(cont));
		}
	}	// namespace infit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INFIT_UNIQUE_HPP
