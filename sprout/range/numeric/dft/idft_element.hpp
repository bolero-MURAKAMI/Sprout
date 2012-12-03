#ifndef SPROUT_RANGE_NUMERIC_DFT_IDFT_ELEMENT_HPP
#define SPROUT_RANGE_NUMERIC_DFT_IDFT_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/dft/idft_element.hpp>

namespace sprout {
	namespace range {
		//
		// idft_element
		//
		template<typename Input>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Input>::value_type
		idft_element(Input const& input, typename sprout::container_traits<Input>::difference_type i) {
			return sprout::idft_element(sprout::begin(input), sprout::end(input), i);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_IDFT_ELEMENT_HPP
