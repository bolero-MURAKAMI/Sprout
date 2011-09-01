#ifndef SPROUT_ALGORITHM_INFIT_TRANSFORM_HPP
#define SPROUT_ALGORITHM_INFIT_TRANSFORM_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace infit {
		namespace detail {
			template<typename Iterator, typename Result, typename UnaryOperation>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> transform_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				UnaryOperation op,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::transform(first, last, result, op),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// transform
		//
		template<typename Iterator, typename Result, typename UnaryOperation>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> transform(
			Iterator first,
			Iterator last,
			Result const& result,
			UnaryOperation op
			)
		{
			return sprout::infit::detail::transform_impl(first, last, result, op, sprout::fixed_begin_offset(result));
		}

		namespace detail {
			template<typename Iterator1, typename Iterator2, typename Result, typename BinaryOperation>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> transform_impl(
				Iterator1 first1,
				Iterator1 last1,
				Iterator2 first2,
				Result const& result,
				BinaryOperation op,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::transform(first1, last1, first2, result, op),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first1, last1), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// transform
		//
		template<typename Iterator1, typename Iterator2, typename Result, typename BinaryOperation>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> transform(
			Iterator1 first1,
			Iterator1 last1,
			Iterator2 first2,
			Result const& result,
			BinaryOperation op
			)
		{
			return sprout::infit::detail::transform_impl(first1, last1, first2, result, op, sprout::fixed_begin_offset(result));
		}
	}	// namespace infit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INFIT_TRANSFORM_HPP
