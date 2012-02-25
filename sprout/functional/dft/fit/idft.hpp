#ifndef SPROUT_FUNCTIONAL_DFT_FIT_IDFT_HPP
#define SPROUT_FUNCTIONAL_DFT_FIT_IDFT_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/functional/dft/fixed/idft.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type idft_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::idft(first, last, result)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// idft
		//
		template<typename InputIterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type idft(
			InputIterator first,
			InputIterator last,
			Result const& result
			)
		{
			return sprout::fit::detail::idft_impl(first, last, result, sprout::fixed_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_DFT_FIT_IDFT_HPP
