#ifndef SPROUT_INDEX_TUPLE_INDEX_RANGE_HPP
#define SPROUT_INDEX_TUPLE_INDEX_RANGE_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/index_tuple/detail/make_indexes_helper.hpp>

namespace sprout {
	//
	// index_range
	//
	namespace detail {
		template<typename IndexTuple, sprout::index_t Next>
		struct index_range_next;
		template<sprout::index_t... Indexes, sprout::index_t Next>
		struct index_range_next<sprout::index_tuple<Indexes...>, Next> {
		public:
			typedef sprout::index_tuple<Indexes..., (Indexes + Next)...> type;
		};

		template<typename IndexTuple, sprout::index_t Next, sprout::index_t Tail>
		struct index_range_next2;
		template<sprout::index_t... Indexes, sprout::index_t Next, sprout::index_t Tail>
		struct index_range_next2<sprout::index_tuple<Indexes...>, Next, Tail> {
		public:
			typedef sprout::index_tuple<Indexes..., (Indexes + Next)..., Tail> type;
		};

		template<sprout::index_t First, sprout::index_t Step, std::size_t N, typename Enable = void>
		struct index_range_impl;
		template<sprout::index_t First, sprout::index_t Step, std::size_t N>
		struct index_range_impl<
			First, Step, N,
			typename std::enable_if<(N == 0)>::type
		> {
		public:
			typedef sprout::index_tuple<> type;
		};
		template<sprout::index_t First, sprout::index_t Step, std::size_t N>
		struct index_range_impl<
			First, Step, N,
			typename std::enable_if<(N == 1)>::type
		> {
		public:
			typedef sprout::index_tuple<First> type;
		};
		template<sprout::index_t First, sprout::index_t Step, std::size_t N>
		struct index_range_impl<
			First, Step, N,
			typename std::enable_if<(N > 1 && N % 2 == 0)>::type
		>
			: public sprout::detail::index_range_next<
				typename sprout::detail::index_range_impl<First, Step, N / 2>::type,
				First + N / 2 * Step
			>
		{};
		template<sprout::index_t First, sprout::index_t Step, std::size_t N>
		struct index_range_impl<
			First, Step, N,
			typename std::enable_if<(N > 1 && N % 2 == 1)>::type
		>
			: public sprout::detail::index_range_next2<
				typename sprout::detail::index_range_impl<First, Step, N / 2>::type,
				First + N / 2 * Step,
				First + (N - 1) * Step
			>
		{};
	}	// namespace detail
	template<sprout::index_t First, sprout::index_t Last, sprout::index_t Step = 1>
	struct index_range
		: public sprout::detail::make_indexes_helper<
			sprout::detail::index_range_impl<
				First, Step, ((Last - First) + (Step - 1)) / Step
			>
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_RANGE_HPP
