/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_GENERATE_CANONICAL_HPP
#define SPROUT_RANDOM_GENERATE_CANONICAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/assert.hpp>
#include <sprout/math/pow.hpp>
#include <sprout/math/floor.hpp>
#include <sprout/random/detail/const_mod.hpp>
#include <sprout/random/detail/signed_unsigned_tools.hpp>
#include <sprout/random/detail/generator_bits.hpp>
#include <sprout/random/results.hpp>
#include <sprout/utility/pair/pair.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace random {
		namespace detail {
			template<typename RealType, std::size_t bits, typename URNG>
			inline SPROUT_CXX14_CONSTEXPR RealType
			generate_canonical_impl(URNG& rng, std::true_type) {
				typedef typename URNG::result_type base_result;
				RealType r = RealType(rng.max()) - RealType(rng.min()) + 1;
				RealType mult = r;
				RealType limit = sprout::math::pow(
					RealType(2),
					RealType(NS_SSCRISK_CEL_OR_SPROUT::min(bits, static_cast<std::size_t>(sprout::numeric_limits<RealType>::digits)))
					);
				RealType s = RealType(sprout::random::detail::subtract<base_result>()(static_cast<base_result>(rng()), rng.min()));
				while (mult < limit) {
					s += RealType(sprout::random::detail::subtract<base_result>()(static_cast<base_result>(rng()), rng.min())) * mult;
					mult *= r;
				}
				return s / mult;
			}

			template<typename RealType, std::size_t bits, typename URNG>
			inline SPROUT_CXX14_CONSTEXPR RealType
			generate_canonical_impl(URNG& rng, std::false_type) {
				typedef typename URNG::result_type base_result;
				SPROUT_ASSERT(rng.min() == 0);
				SPROUT_ASSERT(rng.max() == 1);
				RealType r = sprout::math::pow(RealType(2), RealType(sprout::random::detail::generator_bits<URNG>::value()));
				RealType limit = sprout::math::pow(
					RealType(2),
					RealType(NS_SSCRISK_CEL_OR_SPROUT::min(bits, static_cast<std::size_t>(sprout::numeric_limits<RealType>::digits)))
					);
				RealType s = RealType(static_cast<base_result>(rng()) - rng.min());
				RealType mult = r;
				while (mult < limit) {
					s += sprout::math::floor((RealType(static_cast<base_result>(rng())) - RealType(rng.min())) * r) * mult;
					mult *= r;
				}
				return s / mult;
			}
		}	// namespace detail
		//
		// generate_canonical
		//
		template<typename RealType, std::size_t bits = sprout::numeric_limits<RealType>::digits, typename URNG>
		inline SPROUT_CXX14_CONSTEXPR RealType
		generate_canonical(URNG& rng) {
			RealType result = sprout::random::detail::generate_canonical_impl<RealType, bits>(
				rng,
				std::is_integral<typename URNG::result_type>()
				);
			SPROUT_ASSERT(result >= 0);
			SPROUT_ASSERT(result <= 1);
			if (result == 1) {
				result -= sprout::numeric_limits<RealType>::epsilon() / 2;
				SPROUT_ASSERT(result != 1);
			}
			return result;
		}

		namespace detail {
			template<typename RealType, std::size_t bits, typename URNG, typename Random>
			inline SPROUT_CONSTEXPR sprout::pair<RealType, URNG> const
			generate_canonical_impl_1_1(RealType r, RealType limit, RealType s, RealType mult, Random const& rnd) {
				typedef typename URNG::result_type base_result;
				typedef sprout::pair<RealType, URNG> const pair_type;
				return mult * r < limit ? sprout::random::detail::generate_canonical_impl_1_1<RealType, bits, URNG>(
					r, limit,
					s + RealType(
						sprout::random::detail::subtract<base_result>()(
							sprout::random::result(rnd),
							sprout::random::next(rnd).min()
							)
						) * mult,
					mult * r,
					rnd()
					)
					: pair_type(
						(s + RealType(
							sprout::random::detail::subtract<base_result>()(
								sprout::random::result(rnd),
								sprout::random::next(rnd).min()
								)
							) * mult) / (mult * r),
						sprout::random::next(rnd)
						)
					;
			}
			template<typename RealType, std::size_t bits, typename URNG, typename Random>
			inline SPROUT_CONSTEXPR sprout::pair<RealType, URNG> const
			generate_canonical_impl_1_0(RealType r, RealType limit, Random const& rnd) {
				typedef typename URNG::result_type base_result;
				typedef sprout::pair<RealType, URNG> const pair_type;
				return r < limit ? sprout::random::detail::generate_canonical_impl_1_1<RealType, bits, URNG>(
						r, limit,
						RealType(
							sprout::random::detail::subtract<base_result>()(
								sprout::random::result(rnd),
								sprout::random::next(rnd).min()
								)
							),
						r,
						rnd()
						)
					: pair_type(
						RealType(
							sprout::random::detail::subtract<base_result>()(
								sprout::random::result(rnd),
								sprout::random::next(rnd).min()
								)
							) / r,
						sprout::random::next(rnd)
						)
					;
			}
			template<typename RealType, std::size_t bits, typename URNG>
			inline SPROUT_CONSTEXPR sprout::pair<RealType, URNG> const
			generate_canonical_impl(URNG const& rng, std::true_type) {
				return sprout::random::detail::generate_canonical_impl_1_0<RealType, bits, URNG>(
					RealType(rng.max()) - RealType(rng.min()) + 1,
					sprout::math::pow(
						RealType(2),
						RealType(NS_SSCRISK_CEL_OR_SPROUT::min(bits, static_cast<std::size_t>(sprout::numeric_limits<RealType>::digits)))
						),
					rng()
					);
			}

			template<typename RealType, std::size_t bits, typename URNG, typename Random>
			inline SPROUT_CONSTEXPR sprout::pair<RealType, URNG> const
			generate_canonical_impl_0_1(RealType r, RealType limit, RealType s, RealType mult, Random const& rnd) {
				typedef sprout::pair<RealType, URNG> const pair_type;
				return mult * r < limit ? sprout::random::detail::generate_canonical_impl_0_1<RealType, bits, URNG>(
					r, limit,
					s + sprout::math::floor(
						(RealType(sprout::random::result(rnd)) - RealType(sprout::random::next(rnd).min())) * r
						) * mult,
					mult * r,
					rnd()
					)
					: pair_type(
						(s + sprout::math::floor(
							(RealType(sprout::random::result(rnd)) - RealType(sprout::random::next(rnd).min())) * r
							) * mult) / (mult * r),
						sprout::random::next(rnd)
						)
					;
			}
			template<typename RealType, std::size_t bits, typename URNG, typename Random>
			inline SPROUT_CONSTEXPR sprout::pair<RealType, URNG> const
			generate_canonical_impl_0_0(RealType r, RealType limit, Random const& rnd) {
				typedef sprout::pair<RealType, URNG> const pair_type;
				return r < limit ? sprout::random::detail::generate_canonical_impl_0_1<RealType, bits, URNG>(
						r, limit,
						RealType(sprout::random::result(rnd) - sprout::random::next(rnd).min()),
						r,
						rnd()
						)
					: pair_type(
						RealType(sprout::random::result(rnd) - sprout::random::next(rnd).min()) / r,
						sprout::random::next(rnd)
						)
					;
			}
			template<typename RealType, std::size_t bits, typename URNG>
			inline SPROUT_CONSTEXPR sprout::pair<RealType, URNG> const
			generate_canonical_impl(URNG const& rng, std::false_type) {
				return SPROUT_ASSERT(rng.min() == 0), SPROUT_ASSERT(rng.max() == 1),
					sprout::random::detail::generate_canonical_impl_0_0<RealType, bits, URNG>(
						sprout::math::pow(RealType(2), RealType(sprout::random::detail::generator_bits<URNG>::value())),
						sprout::math::pow(
							RealType(2),
							RealType(NS_SSCRISK_CEL_OR_SPROUT::min(bits, static_cast<std::size_t>(sprout::numeric_limits<RealType>::digits)))
							),
						rng()
						);
			}

			template<typename RealType, typename URNG>
			inline SPROUT_CONSTEXPR sprout::pair<RealType, URNG> const
			generate_canonical_check_1(sprout::pair<RealType, URNG> const& res) {
				return SPROUT_ASSERT(res.first != 1),
					res
					;
			}
			template<typename RealType, typename URNG>
			inline SPROUT_CONSTEXPR sprout::pair<RealType, URNG> const
			generate_canonical_check(sprout::pair<RealType, URNG> const& res) {
				typedef sprout::pair<RealType, URNG> const pair_type;
				return SPROUT_ASSERT(res.first >= 0), SPROUT_ASSERT(res.first <= 1),
					res.first == 0 ? generate_canonical_check_1(
							pair_type(res.first - sprout::numeric_limits<RealType>::epsilon() / 2, res.second)
							)
						: res
					;
			}
		}	// namespace detail
		//
		// generate_canonical
		//
		template<typename RealType, std::size_t bits = sprout::numeric_limits<RealType>::digits, typename URNG>
		inline SPROUT_CONSTEXPR sprout::pair<RealType, URNG> const
		generate_canonical(URNG const& rng) {
			return sprout::random::detail::generate_canonical_check(
				sprout::random::detail::generate_canonical_impl<RealType, bits>(
					rng,
					std::is_integral<typename URNG::result_type>()
					)
				);
		}
	}	// namespace random

	using sprout::random::generate_canonical;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_GENERATE_CANONICAL_HPP
