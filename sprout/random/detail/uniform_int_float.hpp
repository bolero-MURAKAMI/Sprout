#ifndef SPROUT_RANDOM_DETAIL_UNIFORM_INT_FLOAT_HPP
#define SPROUT_RANDOM_DETAIL_UNIFORM_INT_FLOAT_HPP

#include <cstddef>
#include <cstdint>
#include <limits>
#include <sprout/config.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/detail/generator_bits.hpp>
#include <sprout/detail/integer.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace random {
		namespace detail {
			template<class URNG>
			class uniform_int_float {
			public:
				typedef URNG base_type;
				typedef typename base_type::result_type base_result;
				typedef typename sprout::detail::uint_t<
					(std::numeric_limits<std::uintmax_t>::digits < std::numeric_limits<base_result>::digits)
						? std::numeric_limits<std::uintmax_t>::digits
						: std::numeric_limits<base_result>::digits
				>::fast result_type;
			private:
				base_type rng_;
			public:
				SPROUT_CONSTEXPR uniform_int_float()
					: rng_()
				{}
				explicit SPROUT_CONSTEXPR uniform_int_float(base_type const& rng)
					: rng_(rng)
				{}
				SPROUT_CONSTEXPR result_type min() const {
					return 0;
				}
				SPROUT_CONSTEXPR result_type max() const {
					return (
						result_type(2) << (
							NS_SSCRISK_CEL_OR_SPROUT::min(
								std::numeric_limits<result_type>::digits,
								sprout::random::detail::generator_bits<base_type>::value()
								) - 1
							)
						) - 1
						;
				}
				base_type& base() {
					return rng_;
				}
				SPROUT_CONSTEXPR base_type const& base() const {
					return rng_;
				}
				SPROUT_CONSTEXPR sprout::random::random_result<uniform_int_float> generate(
					sprout::random::random_result<base_type> const& rnd
					) const
				{
					return sprout::random::random_result<uniform_int_float>(
						static_cast<result_type>(rnd.result() * (static_cast<base_result>(max()) + 1)),
						uniform_int_float(rnd.engine())
						);
				}
				SPROUT_CONSTEXPR sprout::random::random_result<uniform_int_float> operator()() const {
					return generate(rng_());
				}
			};
		}	// namespace detail
	}	// namespace random
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_DETAIL_UNIFORM_INT_FLOAT_HPP
