/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STATEFUL_TYPED_COUNTER_HPP
#define SPROUT_STATEFUL_TYPED_COUNTER_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

	namespace typed_counter_detail {
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
			};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
#if defined(__GNUC__) && !defined(__clang__)
#	pragma GCC diagnostic pop
#endif

			template<int N>
			struct state
				: public sprout::integral_constant<int, N>
			{
				friend SPROUT_CONSTEXPR int adl_counter(tag<N>) {
					return N;
				}
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
	}	// namespace typed_counter_detail
	//
	// counter
	//
	template<
		typename T,
		int N = 1,
		int R = sprout::typed_counter_detail::typed<T>::template state<
			sprout::typed_counter_detail::typed<T>::template counter(sprout::true_type(), typename sprout::typed_counter_detail::typed<T>::template tag<N - 1>()) + N - 1
			>::value
	>
	inline SPROUT_CONSTEXPR int counter() {
		return R;
	}

#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_STATEFUL_TYPED_COUNTER_HPP
