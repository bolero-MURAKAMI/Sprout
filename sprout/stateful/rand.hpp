/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STATEFUL_RAND_HPP
#define SPROUT_STATEFUL_RAND_HPP

#include <cstdlib>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/random/default_random_engine.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/unique_seed.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/workaround/detail/uniform_int_distribution.hpp>

namespace sprout {
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

	namespace detail {
		typedef sprout::random::default_random_engine rand_generator_type;
		typedef SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION<int> rand_distribution_type;
		typedef sprout::random::random_result<
			sprout::detail::rand_generator_type,
			sprout::detail::rand_distribution_type
		> rand_result_type;

		SPROUT_STATIC_CONSTEXPR std::size_t rand_default_seed = SPROUT_UNIQUE_SEED;
	}	// namespace detail

	namespace rand_detail {
#if defined(__GNUC__) && !defined(__clang__)
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wnon-template-friend"
#endif
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wundefined-inline"
#endif
		template<int N>
		struct tag {
			friend SPROUT_CONSTEXPR int adl_counter(sprout::rand_detail::tag<N>);
			friend SPROUT_CONSTEXPR bool adl_is_srand(sprout::rand_detail::tag<N>);
			friend SPROUT_CONSTEXPR unsigned adl_seed(sprout::rand_detail::tag<N>);
		};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
#if defined(__GNUC__) && !defined(__clang__)
#	pragma GCC diagnostic pop
#endif

		template<int N, bool IsSrand = false, unsigned Seed = 0>
		struct state {
			friend SPROUT_CONSTEXPR int adl_counter(sprout::rand_detail::tag<N>) {
				return N;
			}
			friend SPROUT_CONSTEXPR bool adl_is_srand(sprout::rand_detail::tag<N>) {
				return IsSrand;
			}
			friend SPROUT_CONSTEXPR unsigned adl_seed(sprout::rand_detail::tag<N>) {
				return Seed;
			}
			// generate a next random number
			SPROUT_STATIC_CONSTEXPR sprout::detail::rand_result_type result
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER((
					!IsSrand
						? sprout::rand_detail::state<
							N - 1,
							adl_is_srand(sprout::rand_detail::tag<N - 1>()),
							adl_seed(sprout::rand_detail::tag<N - 1>())
							>::result()
						: sprout::detail::rand_result_type(
							Seed,
							sprout::detail::rand_generator_type(Seed),
							sprout::detail::rand_distribution_type(0, RAND_MAX)
							)
					))
				;
			SPROUT_STATIC_CONSTEXPR int value = result;
		};
		template<int N, bool IsSrand, unsigned Seed>
		SPROUT_CONSTEXPR_OR_CONST sprout::detail::rand_result_type sprout::rand_detail::state<N, IsSrand, Seed>::result
			SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER((
				!IsSrand
					? sprout::rand_detail::state<
						N - 1,
						adl_is_srand(sprout::rand_detail::tag<N - 1>()),
						adl_seed(sprout::rand_detail::tag<N - 1>())
						>::result()
					: sprout::detail::rand_result_type(
						0,
						sprout::detail::rand_generator_type(Seed),
						sprout::detail::rand_distribution_type(0, RAND_MAX)
						)
				))
			;
		template<int N, bool IsSrand, unsigned Seed>
		SPROUT_CONSTEXPR_OR_CONST int sprout::rand_detail::state<N, IsSrand, Seed>::value;
		template<bool IsSrand, unsigned Seed>
		struct state<0, IsSrand, Seed> {
			friend SPROUT_CONSTEXPR int adl_counter(sprout::rand_detail::tag<0>) {
				return 0;
			}
			friend SPROUT_CONSTEXPR bool adl_is_srand(sprout::rand_detail::tag<0>) {
				return IsSrand;
			}
			friend SPROUT_CONSTEXPR unsigned adl_seed(sprout::rand_detail::tag<0>) {
				return Seed;
			}
			// generate a first random number between [0, RAND_MAX]
			SPROUT_STATIC_CONSTEXPR sprout::detail::rand_result_type result
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER((
					!IsSrand
						? sprout::detail::rand_distribution_type(0, RAND_MAX)
							(sprout::as_const(sprout::detail::rand_generator_type(!IsSrand ? sprout::detail::rand_default_seed : Seed)))
						: sprout::detail::rand_result_type(
							Seed,
							sprout::detail::rand_generator_type(Seed),
							sprout::detail::rand_distribution_type(0, RAND_MAX)
							)
					))
				;
			static SPROUT_CONSTEXPR int value = result;
		};
		template<bool IsSrand, unsigned Seed>
		SPROUT_CONSTEXPR_OR_CONST sprout::detail::rand_result_type sprout::rand_detail::state<0, IsSrand, Seed>::result
			SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(
				!IsSrand
					? sprout::detail::rand_distribution_type(0, RAND_MAX)
						(sprout::as_const(sprout::detail::rand_generator_type(!IsSrand ? sprout::detail::rand_default_seed : Seed)))
					: sprout::detail::rand_result_type(
						Seed,
						sprout::detail::rand_generator_type(Seed),
						sprout::detail::rand_distribution_type(0, RAND_MAX)
						)
				)
			;
		template<bool IsSrand, unsigned Seed>
		SPROUT_CONSTEXPR_OR_CONST int sprout::rand_detail::state<0, IsSrand, Seed>::value;

		template<int N, int = adl_counter(sprout::rand_detail::tag<N>())>
		inline SPROUT_CONSTEXPR bool check(int, sprout::rand_detail::tag<N>) {
			return true;
		}
		template<int N>
		inline SPROUT_CONSTEXPR bool check(long, sprout::rand_detail::tag<N>) {
			return false;
		}
		template<int N>
		inline SPROUT_CONSTEXPR bool check(bool R = sprout::rand_detail::check(0, sprout::rand_detail::tag<N>())) {
			return R;
		}

		template<int N>
		inline SPROUT_CONSTEXPR int counter(sprout::false_type, sprout::rand_detail::tag<N>) {
			return 0;
		}
		template<int N>
		inline SPROUT_CONSTEXPR int counter(
			sprout::true_type, sprout::rand_detail::tag<N>,
			int R = !sprout::rand_detail::check<N>() ? N
				: counter(sprout::bool_constant<sprout::rand_detail::check<N>()>(), sprout::rand_detail::tag<N + 1>())
			)
		{
			return R;
		}
		template<int N = 0>
		inline SPROUT_CONSTEXPR int counter(int R = sprout::rand_detail::counter(sprout::true_type(), sprout::rand_detail::tag<N>())) {
			return R;
		}
	}	// namespace rand_detail
	//
	// rand
	//
	template<
		int N = 1,
		int R = sprout::rand_detail::state<
			sprout::rand_detail::counter() + N - 1
			>::value
	>
	inline SPROUT_CONSTEXPR int rand() {
		return R;
	}

	//
	// srand
	// srand_return
	//
	template<
		unsigned Seed,
		int N = 1,
		int = sprout::rand_detail::state<
			sprout::rand_detail::counter() + N - 1,
			true, Seed
			>::value
	>
	SPROUT_CXX14_CONSTEXPR void srand() {}
	template<
		unsigned Seed,
		int N = 1,
		int R = sprout::rand_detail::state<
			sprout::rand_detail::counter() + N - 1,
			true, Seed
			>::value
	>
	inline SPROUT_CONSTEXPR unsigned srand_return() {
		return R;
	}

#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_STATEFUL_RAND_HPP
