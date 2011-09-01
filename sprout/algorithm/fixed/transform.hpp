#ifndef SPROUT_ALGORITHM_FIXED_TRANSFORM_HPP
#define SPROUT_ALGORITHM_FIXED_TRANSFORM_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Iterator, typename Result, std::ptrdiff_t... Indexes, typename UnaryOperation>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type transform_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				sprout::index_tuple<Indexes...>,
				UnaryOperation op,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				typename sprout::fixed_container_traits<Result>::size_type size,
				typename sprout::fixed_container_traits<Result>::size_type input_size
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? op(*(first + Indexes - offset))
						: *(sprout::fixed_begin(result) + Indexes)
						)...
					};
			}
		}	// namespace detail
		//
		// transform
		//
		template<typename Iterator, typename Result, typename UnaryOperation>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type transform(
			Iterator first,
			Iterator last,
			Result const& result,
			UnaryOperation op
			)
		{
			return sprout::fixed::detail::transform_impl(
				first,
				last,
				result,
				typename sprout::index_range<0, sprout::fixed_container_traits<Result>::fixed_size>::type(),
				op,
				sprout::fixed_begin_offset(result),
				sprout::size(result),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last)
				);
		}

		namespace detail {
			template<typename Iterator1, typename Iterator2, typename Result, std::ptrdiff_t... Indexes, typename BinaryOperation>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type transform_impl(
				Iterator1 first1,
				Iterator1 last1,
				Iterator2 first2,
				Result const& result,
				sprout::index_tuple<Indexes...>,
				BinaryOperation op,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				typename sprout::fixed_container_traits<Result>::size_type size,
				typename sprout::fixed_container_traits<Result>::size_type input_size
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? op(*(first1 + Indexes - offset), *(first2 + Indexes - offset))
						: *(sprout::fixed_begin(result) + Indexes)
						)...
					};
			}
		}	// namespace detail
		//
		// transform
		//
		template<typename Iterator1, typename Iterator2, typename Result, typename BinaryOperation>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type transform(
			Iterator1 first1,
			Iterator1 last1,
			Iterator2 first2,
			Result const& result,
			BinaryOperation op
			)
		{
			return sprout::fixed::detail::transform_impl(
				first1,
				last1,
				first2,
				result,
				typename sprout::index_range<0, sprout::fixed_container_traits<Result>::fixed_size>::type(),
				op,
				sprout::fixed_begin_offset(result),
				sprout::size(result),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first1, last1)
			);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_TRANSFORM_HPP
