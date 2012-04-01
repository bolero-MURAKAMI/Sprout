#ifndef SPROUT_FUNCTIONAL_DFT_FIT_DFT_HPP
#define SPROUT_FUNCTIONAL_DFT_FIT_DFT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/functional/dft/fixed/dft.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type dft_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::dft(first, last, result)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// dft
		//
		template<typename InputIterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type dft(
			InputIterator first,
			InputIterator last,
			Result const& result
			)
		{
			return sprout::fit::detail::dft_impl(first, last, result, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_DFT_FIT_DFT_HPP
