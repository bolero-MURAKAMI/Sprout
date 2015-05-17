/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STATEFUL_TYPED_SLOT_HPP
#define SPROUT_STATEFUL_TYPED_SLOT_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

	namespace typed_slot_detail {
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
				friend SPROUT_CONSTEXPR std::intmax_t adl_value(tag<N>);
			};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
#if defined(__GNUC__) && !defined(__clang__)
#	pragma GCC diagnostic pop
#endif

			template<int N, std::intmax_t Value>
			struct state
				: public sprout::integral_constant<std::intmax_t, Value>
			{
				friend SPROUT_CONSTEXPR int adl_counter(tag<N>) {
					return N;
				}
				friend SPROUT_CONSTEXPR std::intmax_t adl_value(tag<N>) {
					return Value;
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

			template<int N>
			static SPROUT_CONSTEXPR std::intmax_t val(sprout::false_type, tag<N>) {
				return 0;
			}
			template<int N>
			static SPROUT_CONSTEXPR std::intmax_t val(
				sprout::true_type, tag<N>,
				std::intmax_t R = !check<N>() ? adl_value(tag<N - 1>())
					: val(sprout::bool_constant<check<N>()>(), tag<N + 1>())
				)
			{
				return R;
			}
			template<int N = 1>
			static SPROUT_CONSTEXPR std::intmax_t val(std::intmax_t R = val(sprout::true_type(), tag<N>())) {
				return R;
			}
		};
	}	// namespace typed_slot_detail
	//
	// slot
	//
	template<
		typename T,
		int N = 1,
		std::intmax_t R = sprout::typed_slot_detail::typed<T>::template val(sprout::true_type(), typename sprout::typed_slot_detail::typed<T>::template tag<N>())
	>
	SPROUT_CONSTEXPR std::intmax_t slot() {
		return R;
	}

	//
	// assign_slot
	// assign_slot_return
	//
	template<
		typename T, std::intmax_t Value,
		int N = 1,
		std::intmax_t = sprout::typed_slot_detail::typed<T>::template state<
			sprout::typed_slot_detail::typed<T>::template counter(sprout::true_type(), typename sprout::typed_slot_detail::typed<T>::template tag<N - 1>()) + N - 1,
			Value
			>::value
	>
	SPROUT_CXX14_CONSTEXPR void assign_slot() {}
	template<
		typename T, std::intmax_t Value,
		int N = 1,
		std::intmax_t R = sprout::typed_slot_detail::typed<T>::template state<
			sprout::typed_slot_detail::typed<T>::template counter(sprout::true_type(), typename sprout::typed_slot_detail::typed<T>::template tag<N - 1>()) + N - 1,
			Value
			>::value
	>
	SPROUT_CONSTEXPR std::intmax_t assign_slot_return() {
		return R;
	}

#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_STATEFUL_TYPED_SLOT_HPP
