#ifndef SPROUT_INDEX_TUPLE_HPP
#define SPROUT_INDEX_TUPLE_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	//
	// index_tuple
	//
	template<std::ptrdiff_t... Indexes>
	struct index_tuple {};

	//
	// index_range
	//
	template<
		std::ptrdiff_t First,
		std::ptrdiff_t Last,
		std::ptrdiff_t Step = 1,
		typename Acc = sprout::index_tuple<>,
		bool Break = (First >= Last)
	>
	struct index_range {
		typedef Acc type;
	};
	template<
		std::ptrdiff_t First,
		std::ptrdiff_t Last,
		std::ptrdiff_t Step,
		std::ptrdiff_t... Indexes
	>
	struct index_range<First, Last, Step, sprout::index_tuple<Indexes...>, false>
		: public sprout::index_range<First + Step, Last, Step, sprout::index_tuple<Indexes..., First> >
	{};

	//
	// index_n
	//
	template<
		std::ptrdiff_t I,
		std::ptrdiff_t N,
		typename Acc = sprout::index_tuple<>,
		bool Break = (N == 0)
	>
	struct index_n {
		typedef Acc type;
	};
	template<
		std::ptrdiff_t I,
		std::ptrdiff_t N,
		std::ptrdiff_t... Indexes
	>
	struct index_n<I, N, sprout::index_tuple<Indexes...>, false>
		: public sprout::index_n<I, N - 1, sprout::index_tuple<Indexes..., I> >
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_HPP
