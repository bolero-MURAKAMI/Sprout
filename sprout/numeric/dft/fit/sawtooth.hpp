#ifndef SPROUT_NUMERIC_DFT_FIT_SAWTOOTH_HPP
#define SPROUT_NUMERIC_DFT_FIT_SAWTOOTH_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/dft/fixed/sawtooth.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
			sawtooth_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::value_type const& frequency,
				typename sprout::container_traits<Container>::value_type const& amplitude,
				typename sprout::container_traits<Container>::value_type const& phase,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::sawtooth(cont, frequency, amplitude, phase)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// sawtooth
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
		sawtooth(
			Container const& cont,
			typename sprout::container_traits<Container>::value_type const& frequency = 1,
			typename sprout::container_traits<Container>::value_type const& amplitude = 1,
			typename sprout::container_traits<Container>::value_type const& phase = 0
			)
		{
			return sprout::fit::detail::sawtooth_impl(cont, frequency, amplitude, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIT_SAWTOOTH_HPP
