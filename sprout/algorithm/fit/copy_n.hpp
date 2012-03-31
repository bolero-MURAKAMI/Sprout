#ifndef SPROUT_ALGORITHM_FIT_COPY_N_HPP
#define SPROUT_ALGORITHM_FIT_COPY_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/copy_n.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Size, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type copy_n_impl(
				InputIterator first,
				Size n,
				Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::copy_n(first, n, result)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n, sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// copy_n
		//
		template<typename InputIterator, typename Size, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type copy_n(
			InputIterator first,
			Size n,
			Result const& result
			)
		{
			return sprout::fit::detail::copy_n_impl(first, n, result, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_COPY_N_HPP
