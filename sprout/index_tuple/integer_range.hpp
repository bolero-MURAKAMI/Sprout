#ifndef SPROUT_INDEX_TUPLE_INTEGER_RANGE_HPP
#define SPROUT_INDEX_TUPLE_INTEGER_RANGE_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/integer_seq.hpp>
#include <sprout/index_tuple/detail/make_indexes_helper.hpp>

namespace sprout {
	//
	// integer_range
	//
	namespace detail {
		template<typename T, typename Seq, T Next>
		struct integer_range_next_even;
		template<typename T, T... Is, T Next>
		struct integer_range_next_even<T, sprout::integer_seq<T, Is...>, Next>
			: public sprout::integer_seq<T, Is..., (Is + Next)...>
		{};

		template<typename T, typename Seq, T Next, T Tail>
		struct integer_range_next_odd;
		template<typename T, T... Is, T Next, T Tail>
		struct integer_range_next_odd<T, sprout::integer_seq<T, Is...>, Next, Tail>
			 : public sprout::integer_seq<T, Is..., (Is + Next)..., Tail>
		{};

		template<typename T, T First, std::ptrdiff_t Step, std::size_t N, typename Enable = void>
		struct integer_range_impl;
		template<typename T, T First, std::ptrdiff_t Step, std::size_t N>
		struct integer_range_impl<
			T, First, Step, N,
			typename std::enable_if<(N == 0)>::type
		>
			: public sprout::integer_seq<T>
		{};
		template<typename T, T First, std::ptrdiff_t Step, std::size_t N>
		struct integer_range_impl<
			T, First, Step, N,
			typename std::enable_if<(N == 1)>::type
		>
			: public sprout::integer_seq<T, First>
		{};
		template<typename T, T First, std::ptrdiff_t Step, std::size_t N>
		struct integer_range_impl<
			T, First, Step, N,
			typename std::enable_if<(N > 1 && N % 2 == 0)>::type
		>
			: public sprout::detail::integer_range_next_even<
				T, typename sprout::detail::integer_range_impl<T, First, Step, N / 2>::type,
				N / 2 * Step
			>
		{};
		template<typename T, T First, std::ptrdiff_t Step, std::size_t N>
		struct integer_range_impl<
			T, First, Step, N,
			typename std::enable_if<(N > 1 && N % 2 == 1)>::type
		>
			: public sprout::detail::integer_range_next_odd<
				T, typename sprout::detail::integer_range_impl<T, First, Step, N / 2>::type,
				N / 2 * Step, First + (N - 1) * Step
			>
		{};
	}	// namespace detail
	template<typename T, T First, T Last, std::ptrdiff_t Step = 1>
	struct integer_range
		: public sprout::detail::make_indexes_helper<
			sprout::detail::integer_range_impl<
				T, First, Step, ((Last - First) + (Step - 1)) / Step
			>
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INTEGER_RANGE_HPP
