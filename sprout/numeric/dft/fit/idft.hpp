#ifndef SPROUT_NUMERIC_DFT_FIT_IDFT_HPP
#define SPROUT_NUMERIC_DFT_FIT_IDFT_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/dft/fixed/idft.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/pit/pit.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename ForwardIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			idft_impl(
				ForwardIterator first, ForwardIterator last, Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::idft(first, last, result)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(sprout::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// idft
		//
		template<typename ForwardIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		idft(ForwardIterator first, ForwardIterator last, Result const& result) {
			return sprout::fit::detail::idft_impl(first, last, result, sprout::internal_begin_offset(result));
		}

		template<typename Result, typename ForwardIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		idft(ForwardIterator first, ForwardIterator last) {
			return sprout::fit::idft(first, last, sprout::pit<Result>());
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIT_IDFT_HPP
