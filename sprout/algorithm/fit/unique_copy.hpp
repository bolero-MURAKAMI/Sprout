#ifndef SPROUT_ALGORITHM_FIT_UNIQUE_COPY_HPP
#define SPROUT_ALGORITHM_FIT_UNIQUE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/unique_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/detail/overlap_count.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Iterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type unique_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::unique_copy(first, last, result)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last) - sprout::detail::overlap_count(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename Iterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type unique_copy(
			Iterator first,
			Iterator last,
			Result const& result
			)
		{
			return sprout::fit::detail::unique_copy_impl(first, last, result, sprout::fixed_begin_offset(result));
		}

		namespace detail {
			template<typename Iterator, typename Result, typename BinaryPredicate>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type unique_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				BinaryPredicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::unique_copy(first, last, result, pred)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last) - sprout::detail::overlap_count(first, last, pred), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename Iterator, typename Result, typename BinaryPredicate>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type unique_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			BinaryPredicate pred
			)
		{
			return sprout::fit::detail::unique_copy_impl(first, last, result, pred, sprout::fixed_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_UNIQUE_COPY_HPP
