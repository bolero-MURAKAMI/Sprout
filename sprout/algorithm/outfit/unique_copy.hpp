#ifndef SPROUT_ALGORITHM_OUTFIT_UNIQUE_COPY_HPP
#define SPROUT_ALGORITHM_OUTFIT_UNIQUE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/unique_copy.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Iterator, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> unique_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::unique_copy(first, last, result),
					offset,
					offset + sprout::size(result)
					);
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename Iterator, typename Result>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> unique_copy(
			Iterator first,
			Iterator last,
			Result const& result
			)
		{
			return sprout::outfit::detail::unique_copy_impl(first, last, result, sprout::fixed_begin_offset(result));
		}

		namespace detail {
			template<typename Iterator, typename Result, typename BinaryPredicate>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> unique_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				BinaryPredicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::unique_copy(first, last, result, pred),
					offset,
					offset + sprout::size(result)
					);
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename Iterator, typename Result, typename BinaryPredicate>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> unique_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			BinaryPredicate pred
			)
		{
			return sprout::outfit::detail::unique_copy_impl(first, last, result, pred, sprout::fixed_begin_offset(result));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_UNIQUE_COPY_HPP
