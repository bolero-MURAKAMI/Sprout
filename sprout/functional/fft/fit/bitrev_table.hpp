#ifndef SPROUT_FUNCTIONAL_FFT_FIT_BITREV_TABLE_HPP
#define SPROUT_FUNCTIONAL_FFT_FIT_BITREV_TABLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/functional/fft/fixed/bitrev_table.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type bitrev_table_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::bitrev_table(cont)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// bitrev_table
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type bitrev_table(
			Container const& cont
			)
		{
			return sprout::fit::detail::bitrev_table_impl(cont, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_FFT_FIT_BITREV_TABLE_HPP
