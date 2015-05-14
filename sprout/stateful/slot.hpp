/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STATEFUL_SLOT_HPP
#define SPROUT_STATEFUL_SLOT_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/assert.hpp>

namespace sprout {
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

	namespace detail {
		SPROUT_STATIC_CONSTEXPR std::size_t slot_default_call_limit = 128;
	}	// namespace detail

	namespace slot_detail {
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
			friend SPROUT_CONSTEXPR int adl_counter(sprout::slot_detail::tag<N>);
			friend SPROUT_CONSTEXPR int adl_id(sprout::slot_detail::tag<N>);
			friend SPROUT_CONSTEXPR std::intmax_t adl_value(sprout::slot_detail::tag<N>);
			template<int I>
			friend SPROUT_CONSTEXPR std::intmax_t adl_get(sprout::slot_detail::tag<N>, sprout::integral_constant<int, I>);
		};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
#if defined(__GNUC__) && !defined(__clang__)
#	pragma GCC diagnostic pop
#endif

		template<int N, int ID, std::intmax_t Value>
		struct state {
			friend SPROUT_CONSTEXPR int adl_counter(sprout::slot_detail::tag<N>) {
				return N;
			}
			friend SPROUT_CONSTEXPR int adl_id(sprout::slot_detail::tag<N>) {
				return ID;
			}
			friend SPROUT_CONSTEXPR std::intmax_t adl_value(sprout::slot_detail::tag<N>) {
				return Value;
			}
			template<int I>
			friend SPROUT_CONSTEXPR std::intmax_t adl_get(sprout::slot_detail::tag<N>, sprout::integral_constant<int, I>) {
				return get<I>();
			}
			template<int I>
			static SPROUT_CONSTEXPR std::intmax_t get() {
				return I == ID ? Value
					: state<
						N - 1,
						adl_id(sprout::slot_detail::tag<N - 1>()),
						adl_value(sprout::slot_detail::tag<N - 1>())
						>::template get<I>()
					;
			}
		};
		template<int ID, std::intmax_t Value>
		struct state<1, ID, Value> {
			friend SPROUT_CONSTEXPR int adl_counter(sprout::slot_detail::tag<1>) {
				return 1;
			}
			friend SPROUT_CONSTEXPR int adl_id(sprout::slot_detail::tag<1>) {
				return ID;
			}
			friend SPROUT_CONSTEXPR std::intmax_t adl_value(sprout::slot_detail::tag<1>) {
				return Value;
			}
			template<int I>
			friend SPROUT_CONSTEXPR std::intmax_t adl_get(sprout::slot_detail::tag<1>, sprout::integral_constant<int, I>) {
				return get<I>();
			}
			template<int I>
			static SPROUT_CONSTEXPR std::intmax_t get() {
				return SPROUT_ASSERT(I == ID), Value;
			}
		};

		template<int N, int R = adl_counter(sprout::slot_detail::tag<N>())>
		SPROUT_CONSTEXPR int counter(
			int, sprout::slot_detail::tag<N>
			)
		{
			return R;
		}
		SPROUT_CONSTEXPR int counter(
			long, sprout::slot_detail::tag<0>
			)
		{
			return 0;
		}
		template<int N>
		SPROUT_CONSTEXPR int counter(
			long, sprout::slot_detail::tag<N>,
			int R = counter(0, sprout::slot_detail::tag<N - 1>())
			)
		{
			return R;
		}

		template<int I, int N, std::intmax_t R = adl_get(sprout::slot_detail::tag<N>(), sprout::integral_constant<int, I>())>
		SPROUT_CONSTEXPR std::intmax_t get(
			int, sprout::slot_detail::tag<N>
			)
		{
			return R;
		}
		template<int I>
		SPROUT_CONSTEXPR std::intmax_t get(
			long, sprout::slot_detail::tag<0>
			)
		{
			return 0;
		}
		template<int I, int N>
		SPROUT_CONSTEXPR std::intmax_t get(
			long, sprout::slot_detail::tag<N>,
			std::intmax_t R = get<I>(0, sprout::slot_detail::tag<N - 1>())
			)
		{
			return R;
		}
	}	// namespace slot_detail
	//
	// slot
	//
	template<
		int I,
		std::size_t Limit = sprout::detail::slot_default_call_limit,
		std::intmax_t R = sprout::slot_detail::get<I>(0, sprout::slot_detail::tag<Limit>())
	>
	SPROUT_CONSTEXPR std::intmax_t slot() {
		return R;
	}
	//
	// assign_slot
	// assign_slot_return
	//
	template<
		int I,
		std::intmax_t Value,
		std::size_t Limit = sprout::detail::slot_default_call_limit,
		std::intmax_t = sprout::slot_detail::state<
			sprout::slot_detail::counter(0, sprout::slot_detail::tag<Limit>()) + 1,
			I, Value
			>::template get<I>()
	>
	SPROUT_CXX14_CONSTEXPR void assign_slot() {}
	template<
		int I,
		std::intmax_t Value,
		std::size_t Limit = sprout::detail::slot_default_call_limit,
		std::intmax_t R = sprout::slot_detail::state<
			sprout::slot_detail::counter(0, sprout::slot_detail::tag<Limit>()) + 1,
			I, Value
			>::template get<I>()
	>
	SPROUT_CONSTEXPR std::intmax_t assign_slot_return() {
		return R;
	}

#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_STATEFUL_SLOT_HPP
