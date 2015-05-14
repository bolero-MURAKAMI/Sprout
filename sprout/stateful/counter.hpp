/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STATEFUL_COUNTER_HPP
#define SPROUT_STATEFUL_COUNTER_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>

namespace sprout {
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

	namespace detail {
		SPROUT_STATIC_CONSTEXPR std::size_t counter_default_call_limit = 128;
	}	// namespace detail

	namespace counter_detail {
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
			friend SPROUT_CONSTEXPR int adl_counter(sprout::counter_detail::tag<N>);
		};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
#if defined(__GNUC__) && !defined(__clang__)
#	pragma GCC diagnostic pop
#endif

		template<int N>
		struct state {
			friend SPROUT_CONSTEXPR int adl_counter(sprout::counter_detail::tag<N>) {
				return N;
			}
			SPROUT_STATIC_CONSTEXPR int value = N - 1;
		};
		template<int N>
		SPROUT_CONSTEXPR_OR_CONST int sprout::counter_detail::state<N>::value;
		template<>
		struct state<1> {
			friend SPROUT_CONSTEXPR int adl_counter(sprout::counter_detail::tag<1>) {
				return 1;
			}
			static SPROUT_CONSTEXPR int value = 0;
		};
		SPROUT_CONSTEXPR_OR_CONST int sprout::counter_detail::state<1>::value;

		template<int N, int R = adl_counter(sprout::counter_detail::tag<N>())>
		SPROUT_CONSTEXPR int counter(
			int, sprout::counter_detail::tag<N>
			)
		{
			return R;
		}
		SPROUT_CONSTEXPR int counter(
			long, sprout::counter_detail::tag<0>
			)
		{
			return 0;
		}
		template<int N>
		SPROUT_CONSTEXPR int counter(
			long, sprout::counter_detail::tag<N>,
			int R = counter(0, sprout::counter_detail::tag<N - 1>())
			)
		{
			return R;
		}
	}	// namespace counter_detail
	//
	// counter
	// counter_before
	//
	template<
		std::size_t Limit = sprout::detail::counter_default_call_limit,
		int R = sprout::counter_detail::state<
			sprout::counter_detail::counter(0, sprout::counter_detail::tag<Limit>()) + 1
			>::value
	>
	SPROUT_CONSTEXPR int counter() {
		return R;
	}
	template<
		std::size_t Limit = sprout::detail::counter_default_call_limit,
		int R = sprout::counter_detail::state<
			sprout::counter_detail::counter(0, sprout::counter_detail::tag<Limit>())
			>::value
	>
	SPROUT_CONSTEXPR int counter_before() {
		return R;
	}

#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_STATEFUL_COUNTER_HPP
