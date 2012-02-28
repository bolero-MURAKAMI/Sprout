#ifndef SPROUT_INDEX_TUPLE_HPP
#define SPROUT_INDEX_TUPLE_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	//
	// index_t
	//
	typedef std::ptrdiff_t index_t;

	//
	// index_tuple
	//
	template<sprout::index_t... Indexes>
	struct index_tuple {};

	//
	// index_range
	//
	template<
		sprout::index_t First,
		sprout::index_t Last,
		sprout::index_t Step = 1,
		typename Acc = sprout::index_tuple<>,
		bool Break = (First >= Last)
	>
	struct index_range {
		typedef Acc type;
	};
	template<
		sprout::index_t First,
		sprout::index_t Last,
		sprout::index_t Step,
		sprout::index_t... Indexes
	>
	struct index_range<First, Last, Step, sprout::index_tuple<Indexes...>, false>
		: public sprout::index_range<First + Step, Last, Step, sprout::index_tuple<Indexes..., First> >
	{};

	//
	// index_n
	//
	template<
		sprout::index_t I,
		sprout::index_t N,
		typename Acc = sprout::index_tuple<>,
		bool Break = (N == 0)
	>
	struct index_n {
		typedef Acc type;
	};
	template<
		sprout::index_t I,
		sprout::index_t N,
		sprout::index_t... Indexes
	>
	struct index_n<I, N, sprout::index_tuple<Indexes...>, false>
		: public sprout::index_n<I, N - 1, sprout::index_tuple<Indexes..., I> >
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_HPP
