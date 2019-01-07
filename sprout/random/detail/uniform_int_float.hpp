/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_DETAIL_UNIFORM_INT_FLOAT_HPP
#define SPROUT_RANDOM_DETAIL_UNIFORM_INT_FLOAT_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/detail/generator_bits.hpp>
#include <sprout/random/results.hpp>
#include <sprout/detail/integer.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace random {
		namespace detail {
			template<typename URNG>
			class uniform_int_float {
			public:
				typedef URNG base_type;
				typedef typename base_type::result_type base_result;
				typedef typename sprout::detail::uint_t<
					(sprout::numeric_limits<std::uintmax_t>::digits < sprout::numeric_limits<base_result>::digits)
						? sprout::numeric_limits<std::uintmax_t>::digits
						: sprout::numeric_limits<base_result>::digits
				>::fast result_type;
			private:
				base_type rng_;
			private:
				SPROUT_CONSTEXPR sprout::random::random_result<uniform_int_float> generate(
					sprout::random::random_result<base_type> const& rnd
					) const
				{
					return sprout::random::random_result<uniform_int_float>(
						static_cast<result_type>(sprout::random::result(rnd) * (static_cast<base_result>(max()) + 1)),
						uniform_int_float(sprout::random::next(rnd))
						);
				}
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
								sprout::numeric_limits<result_type>::digits,
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
				SPROUT_CXX14_CONSTEXPR result_type operator()() {
					return static_cast<result_type>(static_cast<base_result>(rng_()) * static_cast<base_result>(max()) + 1);
				}
				SPROUT_CONSTEXPR sprout::random::random_result<uniform_int_float> const operator()() const {
					return generate(rng_());
				}
			};
		}	// namespace detail
	}	// namespace random
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_DETAIL_UNIFORM_INT_FLOAT_HPP
