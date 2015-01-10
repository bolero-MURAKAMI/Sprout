/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INDEX_TUPLE_INTEGER_RANGE_HPP
#define SPROUT_INDEX_TUPLE_INTEGER_RANGE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/integer_sequence.hpp>
#include <sprout/index_tuple/enable_make_indexes.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace detail {
		template<typename T, T First, T Last>
		struct integer_range_default_step
			: public sprout::integral_constant<typename std::make_signed<T>::type, (First <= Last ? 1 : -1)>
		{};
	}	// namespace detail

	namespace detail {
		template<typename T, typename Seq, T Next>
		struct integer_range_next_even;
		template<typename T, T... Is, T Next>
		struct integer_range_next_even<T, sprout::integer_sequence<T, Is...>, Next>
			: public sprout::integer_sequence<T, Is..., (Is + Next)...>
		{};

		template<typename T, typename Seq, T Next, T Tail>
		struct integer_range_next_odd;
		template<typename T, T... Is, T Next, T Tail>
		struct integer_range_next_odd<T, sprout::integer_sequence<T, Is...>, Next, Tail>
			: public sprout::integer_sequence<T, Is..., (Is + Next)..., Tail>
		{};

		template<typename T, T First, typename std::make_signed<T>::type Step, typename std::make_unsigned<T>::type N, typename Enable = void>
		struct integer_range_dispatch;
		template<typename T, T First, typename std::make_signed<T>::type Step, typename std::make_unsigned<T>::type N>
		struct integer_range_dispatch<
			T, First, Step, N,
			typename std::enable_if<(N == 0)>::type
		>
			: public sprout::integer_sequence<T>
		{};
		template<typename T, T First, typename std::make_signed<T>::type Step, typename std::make_unsigned<T>::type N>
		struct integer_range_dispatch<
			T, First, Step, N,
			typename std::enable_if<(N == 1)>::type
		>
			: public sprout::integer_sequence<T, First>
		{};
		template<typename T, T First, typename std::make_signed<T>::type Step, typename std::make_unsigned<T>::type N>
		struct integer_range_dispatch<
			T, First, Step, N,
			typename std::enable_if<(N > 1 && N % 2 == 0)>::type
		>
			: public sprout::detail::integer_range_next_even<
				T, typename sprout::detail::integer_range_dispatch<T, First, Step, N / 2>::type,
				N / 2 * Step
			>
		{};
		template<typename T, T First, typename std::make_signed<T>::type Step, typename std::make_unsigned<T>::type N>
		struct integer_range_dispatch<
			T, First, Step, N,
			typename std::enable_if<(N > 1 && N % 2 == 1)>::type
		>
			: public sprout::detail::integer_range_next_odd<
				T, typename sprout::detail::integer_range_dispatch<T, First, Step, N / 2>::type,
				N / 2 * Step, First + (N - 1) * Step
			>
		{};
		template<typename T, T First, T Last, typename std::make_signed<T>::type Step, typename Enable = void>
		struct integer_range_impl {};
		template<typename T, T First, T Last, typename std::make_signed<T>::type Step>
		struct integer_range_impl<
			T, First, Last, Step,
			typename std::enable_if<((First < Last && Step > 0) || (First > Last && Step < 0) || (First == Last))>::type
		>
			: public sprout::detail::integer_range_dispatch<
				T, First, Step,
				(static_cast<typename std::make_signed<T>::type>(Last - First) + (Step > 0 ? Step - 1 : Step + 1)) / Step
			>
		{};

		template<
			typename T, T First, T Last,
			typename std::make_signed<T>::type Step
		>
		struct integer_range
			: public sprout::enable_make_indexes<
				sprout::detail::integer_range_impl<T, First, Last, Step>
			>
		{
			static_assert(
				(First < Last && Step > 0) || (First > Last && Step < 0) || (First == Last),
				"(First < Last && Step > 0) || (First > Last && Step < 0) || (First == Last)"
				);
		};
	}	// namespace detail
	//
	// integer_range
	//
#if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
	template<
		typename T, T First, T Last,
		typename std::make_signed<T>::type Step = sprout::detail::integer_range_default_step<T, First, Last>::value
	>
	using integer_range = typename sprout::detail::integer_range<T, First, Last, Step>::type;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
	template<
		typename T, T First, T Last,
		typename std::make_signed<T>::type Step = sprout::detail::integer_range_default_step<T, First, Last>::value
	>
	struct integer_range
		: public sprout::detail::integer_range<T, First, Last, Step>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INTEGER_RANGE_HPP
