#ifndef SPROUT_RANDOM_DETAIL_GENERATOR_BITS_HPP
#define SPROUT_RANDOM_DETAIL_GENERATOR_BITS_HPP

#include <cstddef>
#include <limits>
#include <sprout/config.hpp>

namespace sprout {
	namespace random {
		namespace detail {
			template<typename URNG>
			struct generator_bits {
			public:
				static SPROUT_CONSTEXPR std::size_t value() {
					return std::numeric_limits<typename URNG::result_type>::digits;
				}
			};
		}	// namespace detail
	}	// namespace random
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_DETAIL_GENERATOR_BITS_HPP
