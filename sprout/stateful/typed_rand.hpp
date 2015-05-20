/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STATEFUL_TYPED_RAND_HPP
#define SPROUT_STATEFUL_TYPED_RAND_HPP

#include <cstdlib>
#include <sprout/config.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/random/unique_seed.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/stateful/rand.hpp>

namespace sprout {
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

	namespace typed_rand_detail {
		template<typename T>
		struct typed {
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
				friend SPROUT_CONSTEXPR int adl_counter(tag<N>);
				friend SPROUT_CONSTEXPR bool adl_is_srand(tag<N>);
				friend SPROUT_CONSTEXPR unsigned adl_seed(tag<N>);
			};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
#if defined(__GNUC__) && !defined(__clang__)
#	pragma GCC diagnostic pop
#endif

			template<int N, bool IsSrand = false, unsigned Seed = 0>
			struct state {
				friend SPROUT_CONSTEXPR int adl_counter(tag<N>) {
					return N;
				}
				friend SPROUT_CONSTEXPR bool adl_is_srand(tag<N>) {
					return IsSrand;
				}
				friend SPROUT_CONSTEXPR unsigned adl_seed(tag<N>) {
					return Seed;
				}
				// generate a next random number
				SPROUT_STATIC_CONSTEXPR sprout::detail::rand_result_type result
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER((
						!IsSrand
							? state<
								N - 1,
								adl_is_srand(tag<N - 1>()),
								adl_seed(tag<N - 1>())
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
			template<bool IsSrand, unsigned Seed>
			struct state<0, IsSrand, Seed> {
				friend SPROUT_CONSTEXPR int adl_counter(tag<0>) {
					return 0;
				}
				friend SPROUT_CONSTEXPR bool adl_is_srand(tag<0>) {
					return IsSrand;
				}
				friend SPROUT_CONSTEXPR unsigned adl_seed(tag<0>) {
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

			template<int N, int = adl_counter(tag<N>())>
			static SPROUT_CONSTEXPR bool check(int, tag<N>) {
				return true;
			}
			template<int N>
			static SPROUT_CONSTEXPR bool check(long, tag<N>) {
				return false;
			}
			template<int N>
			static SPROUT_CONSTEXPR bool check(bool R = check(0, tag<N>())) {
				return R;
			}

			template<int N>
			static SPROUT_CONSTEXPR int counter(sprout::false_type, tag<N>) {
				return 0;
			}
			template<int N>
			static SPROUT_CONSTEXPR int counter(
				sprout::true_type, tag<N>,
				int R = !check<N>() ? N
					: counter(sprout::bool_constant<check<N>()>(), tag<N + 1>())
				)
			{
				return R;
			}
			template<int N = 0>
			static SPROUT_CONSTEXPR int counter(int R = counter(sprout::true_type(), tag<N>())) {
				return R;
			}
		};
		template<typename T>
		template<int N, bool IsSrand, unsigned Seed>
		SPROUT_CONSTEXPR_OR_CONST sprout::detail::rand_result_type sprout::typed_rand_detail::typed<T>::state<N, IsSrand, Seed>::result
			SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER((
				!IsSrand
					? state<
						N - 1,
						adl_is_srand(tag<N - 1>()),
						adl_seed(tag<N - 1>())
						>::result()
					: sprout::detail::rand_result_type(
						0,
						sprout::detail::rand_generator_type(Seed),
						sprout::detail::rand_distribution_type(0, RAND_MAX)
						)
				))
			;
		template<typename T>
		template<int N, bool IsSrand, unsigned Seed>
		SPROUT_CONSTEXPR_OR_CONST int sprout::typed_rand_detail::typed<T>::state<N, IsSrand, Seed>::value;

		template<typename T>
		template<bool IsSrand, unsigned Seed>
		SPROUT_CONSTEXPR_OR_CONST sprout::detail::rand_result_type sprout::typed_rand_detail::typed<T>::state<0, IsSrand, Seed>::result
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
		template<typename T>
		template<bool IsSrand, unsigned Seed>
		SPROUT_CONSTEXPR_OR_CONST int sprout::typed_rand_detail::typed<T>::state<0, IsSrand, Seed>::value;
	}	// namespace typed_rand_detail
	//
	// rand
	//
	template<
		typename T,
		int N = 1,
		int R = sprout::typed_rand_detail::typed<T>::template state<
			sprout::typed_rand_detail::typed<T>::template counter(sprout::true_type(), typename sprout::typed_rand_detail::typed<T>::template tag<N - 1>()) + N - 1
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
		typename T, unsigned Seed,
		int N = 1,
		int = sprout::typed_rand_detail::typed<T>::template state<
			sprout::typed_rand_detail::typed<T>::template counter(sprout::true_type(), typename sprout::typed_rand_detail::typed<T>::template tag<N - 1>()) + N - 1,
			true, Seed
			>::value
	>
	inline SPROUT_CXX14_CONSTEXPR void srand() {}
	template<
		typename T, unsigned Seed,
		int N = 1,
		int R = sprout::typed_rand_detail::typed<T>::template state<
			sprout::typed_rand_detail::typed<T>::template counter(sprout::true_type(), typename sprout::typed_rand_detail::typed<T>::template tag<N - 1>()) + N - 1,
			true, Seed
			>::value
	>
	inline SPROUT_CONSTEXPR unsigned srand_return() {
		return R;
	}

#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_STATEFUL_TYPED_RAND_HPP
