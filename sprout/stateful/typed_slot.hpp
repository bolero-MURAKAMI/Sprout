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
#include <sprout/assert.hpp>
#include <sprout/stateful/typed_id.hpp>

namespace sprout {
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

	namespace typed_slot_detail {
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
			friend SPROUT_CONSTEXPR int adl_counter(sprout::typed_slot_detail::tag<N>);
			friend SPROUT_CONSTEXPR int adl_key(sprout::typed_slot_detail::tag<N>);
			friend SPROUT_CONSTEXPR std::intmax_t adl_value(sprout::typed_slot_detail::tag<N>);
			template<int K>
			friend SPROUT_CONSTEXPR std::intmax_t adl_get(sprout::typed_slot_detail::tag<N>, sprout::integral_constant<int, K>);
		};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
#if defined(__GNUC__) && !defined(__clang__)
#	pragma GCC diagnostic pop
#endif

		template<int N, int Key, std::intmax_t Value>
		struct state
			: public sprout::integral_constant<std::intmax_t, Value>
		{
			friend SPROUT_CONSTEXPR int adl_counter(sprout::typed_slot_detail::tag<N>) {
				return N;
			}
			friend SPROUT_CONSTEXPR int adl_key(sprout::typed_slot_detail::tag<N>) {
				return Key;
			}
			friend SPROUT_CONSTEXPR std::intmax_t adl_value(sprout::typed_slot_detail::tag<N>) {
				return Value;
			}
			template<int K>
			friend SPROUT_CONSTEXPR std::intmax_t adl_get(sprout::typed_slot_detail::tag<N>, sprout::integral_constant<int, K>) {
				return get<K>();
			}
			template<int K>
			static SPROUT_CONSTEXPR std::intmax_t get() {
				return K == Key ? Value
					: state<
						N - 1,
						adl_key(sprout::typed_slot_detail::tag<N - 1>()),
						adl_value(sprout::typed_slot_detail::tag<N - 1>())
						>::template get<K>()
					;
			}
		};
		template<int Key, std::intmax_t Value>
		struct state<0, Key, Value>
			: public sprout::integral_constant<std::intmax_t, Value>
		{
			friend SPROUT_CONSTEXPR int adl_counter(sprout::typed_slot_detail::tag<0>) {
				return 0;
			}
			friend SPROUT_CONSTEXPR int adl_key(sprout::typed_slot_detail::tag<0>) {
				return Key;
			}
			friend SPROUT_CONSTEXPR std::intmax_t adl_value(sprout::typed_slot_detail::tag<0>) {
				return Value;
			}
			template<int K>
			friend SPROUT_CONSTEXPR std::intmax_t adl_get(sprout::typed_slot_detail::tag<0>, sprout::integral_constant<int, K>) {
				return get<K>();
			}
			template<int K>
			static SPROUT_CONSTEXPR std::intmax_t get() {
				return SPROUT_ASSERT(K == Key), Value;
			}
		};

		template<int N, int = adl_counter(sprout::typed_slot_detail::tag<N>())>
		SPROUT_CONSTEXPR bool check(int, sprout::typed_slot_detail::tag<N>) {
			return true;
		}
		template<int N>
		SPROUT_CONSTEXPR bool check(long, sprout::typed_slot_detail::tag<N>) {
			return false;
		}
		template<int N>
		SPROUT_CONSTEXPR bool check(bool R = sprout::typed_slot_detail::check(0, sprout::typed_slot_detail::tag<N>())) {
			return R;
		}

		template<int N>
		SPROUT_CONSTEXPR int counter(sprout::false_type, sprout::typed_slot_detail::tag<N>) {
			return 0;
		}
		template<int N>
		SPROUT_CONSTEXPR int counter(
			sprout::true_type, sprout::typed_slot_detail::tag<N>,
			int R = !sprout::typed_slot_detail::check(0, sprout::typed_slot_detail::tag<N>()) ? N
				: counter(sprout::bool_constant<sprout::typed_slot_detail::check(0, sprout::typed_slot_detail::tag<N>())>(), sprout::typed_slot_detail::tag<N + 1>())
			)
		{
			return R;
		}
		template<int N = 0>
		SPROUT_CONSTEXPR int counter(int R = sprout::typed_slot_detail::counter(sprout::true_type(), sprout::typed_slot_detail::tag<N>())) {
			return R;
		}

		template<int K, int N>
		SPROUT_CONSTEXPR std::intmax_t get_impl(sprout::false_type, sprout::typed_slot_detail::tag<N>) {
			return 0;
		}
		template<int K, int N>
		SPROUT_CONSTEXPR std::intmax_t get_impl(
			sprout::true_type, sprout::typed_slot_detail::tag<N>,
			std::intmax_t R = !sprout::typed_slot_detail::check(0, sprout::typed_slot_detail::tag<N>()) ? adl_get(sprout::typed_slot_detail::tag<N - 1>(), sprout::integral_constant<int, K>())
				: get_impl<K>(sprout::bool_constant<sprout::typed_slot_detail::check(0, sprout::typed_slot_detail::tag<N>())>(), sprout::typed_slot_detail::tag<N + 1>())
			)
		{
			return R;
		}
		template<int K, int N = 0>
		SPROUT_CONSTEXPR std::intmax_t get(int R = sprout::typed_slot_detail::get_impl<K>(sprout::true_type(), sprout::typed_slot_detail::tag<N>())) {
			return R;
		}
	}	// namespace typed_slot_detail
	//
	// slot
	//
	template<
		typename T,
		std::intmax_t R = sprout::typed_slot_detail::get<sprout::typed_id<T>::value>()
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
		int N = 0,
		std::intmax_t = sprout::typed_slot_detail::state<
			sprout::typed_slot_detail::counter(sprout::true_type(), sprout::typed_slot_detail::tag<N>()),
			sprout::typed_id<T>::value, Value
			>::value
	>
	SPROUT_CXX14_CONSTEXPR void assign_slot() {}
	template<
		typename T, std::intmax_t Value,
		int N = 0,
		std::intmax_t R = sprout::typed_slot_detail::state<
			sprout::typed_slot_detail::counter(sprout::true_type(), sprout::typed_slot_detail::tag<N>()),
			sprout::typed_id<T>::value, Value
			>::value
	>
	SPROUT_CONSTEXPR std::intmax_t assign_slot_return() {
		return R;
	}

#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_STATEFUL_TYPED_SLOT_HPP
