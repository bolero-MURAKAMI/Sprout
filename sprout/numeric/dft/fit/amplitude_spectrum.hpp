#ifndef SPROUT_NUMERIC_DFT_FIT_AMPLITUDE_SPECTRUM_HPP
#define SPROUT_NUMERIC_DFT_FIT_AMPLITUDE_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/dft/fixed/amplitude_spectrum.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type amplitude_spectrum_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::amplitude_spectrum(first, last, result)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// amplitude_spectrum
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type amplitude_spectrum(
			InputIterator first,
			InputIterator last,
			Result const& result
			)
		{
			return sprout::fit::detail::amplitude_spectrum_impl(first, last, result, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIT_AMPLITUDE_SPECTRUM_HPP
