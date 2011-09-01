#ifndef SPROUT_ALGORITHM_INFIT_MERGE_HPP
#define SPROUT_ALGORITHM_INFIT_MERGE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/merge.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace infit {
		namespace detail {
			template<typename Iterator1, typename Iterator2, typename Result, typename Compare>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> merge_impl(
				Iterator1 first1,
				Iterator1 last1,
				Iterator2 first2,
				Iterator2 last2,
				Result const& result,
				Compare comp,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::merge(first1, last1, first2, last2, result, comp),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(
						NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first1, last1) + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first2, last2),
						sprout::size(result)
						)
					);
			}
		}	// namespace detail
		//
		// merge
		//
		template<typename Iterator1, typename Iterator2, typename Result, typename Compare>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> merge(
			Iterator1 first1,
			Iterator1 last1,
			Iterator2 first2,
			Iterator2 last2,
			Result const& result,
			Compare comp
			)
		{
			return sprout::infit::detail::merge_impl(first1, last1, first2, last2, result, comp, sprout::fixed_begin_offset(result));
		}

		namespace detail {
			template<typename Iterator1, typename Iterator2, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> merge_impl(
				Iterator1 first1,
				Iterator1 last1,
				Iterator2 first2,
				Iterator2 last2,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::merge(first1, last1, first2, last2, result),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(
						NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first1, last1) + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first2, last2),
						sprout::size(result)
						)
					);
			}
		}	// namespace detail
		//
		// merge
		//
		template<typename Iterator1, typename Iterator2, typename Result>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> merge(
			Iterator1 first1,
			Iterator1 last1,
			Iterator2 first2,
			Iterator2 last2,
			Result const& result
			)
		{
			return sprout::infit::detail::merge_impl(first1, last1, first2, last2, result, sprout::fixed_begin_offset(result));
		}
	}	// namespace infit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INFIT_MERGE_HPP
