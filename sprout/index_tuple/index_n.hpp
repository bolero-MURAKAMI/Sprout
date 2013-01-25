#ifndef SPROUT_INDEX_TUPLE_INDEX_N_HPP
#define SPROUT_INDEX_TUPLE_INDEX_N_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/index_tuple/detail/make_indexes_helper.hpp>

namespace sprout {
	//
	// index_n
	//
	namespace detail {
		template<typename IndexTuple>
		struct index_n_next;
		template<sprout::index_t... Indexes>
		struct index_n_next<sprout::index_tuple<Indexes...>> {
		public:
			typedef sprout::index_tuple<Indexes..., Indexes...> type;
		};

		template<typename IndexTuple, sprout::index_t Tail>
		struct index_n_next2;
		template<sprout::index_t... Indexes, sprout::index_t Tail>
		struct index_n_next2<sprout::index_tuple<Indexes...>, Tail> {
		public:
			typedef sprout::index_tuple<Indexes..., Indexes..., Tail> type;
		};

		template<sprout::index_t I, std::size_t N, typename Enable = void>
		struct index_n_impl;
		template<sprout::index_t I, std::size_t N>
		struct index_n_impl<
			I, N,
			typename std::enable_if<(N == 0)>::type
		> {
		public:
			typedef sprout::index_tuple<> type;
		};
		template<sprout::index_t I, std::size_t N>
		struct index_n_impl<
			I, N,
			typename std::enable_if<(N == 1)>::type
		> {
		public:
			typedef sprout::index_tuple<I> type;
		};
		template<sprout::index_t I, std::size_t N>
		struct index_n_impl<
			I, N,
			typename std::enable_if<(N > 1 && N % 2 == 0)>::type
		>
			: public sprout::detail::index_n_next<
				typename sprout::detail::index_n_impl<I, N / 2>::type
			>
		{};
		template<sprout::index_t I, std::size_t N>
		struct index_n_impl<
			I, N,
			typename std::enable_if<(N > 1 && N % 2 == 1)>::type
		>
			: public sprout::detail::index_n_next2<
				typename sprout::detail::index_n_impl<I, N / 2>::type,
				I
			>
		{};
	}	// namespace detail
	template<sprout::index_t I, std::size_t N>
	struct index_n
		: public sprout::detail::make_indexes_helper<
			sprout::detail::index_n_impl<I, N>
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_N_HPP
