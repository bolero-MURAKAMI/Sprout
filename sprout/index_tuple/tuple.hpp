#ifndef SPROUT_INDEX_TUPLE_TUPLE_HPP
#define SPROUT_INDEX_TUPLE_TUPLE_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<sprout::index_t... Indexes>
	struct tuple_size<sprout::index_tuple<Indexes...> >
		: public std::integral_constant<std::size_t, sizeof...(Indexes)>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, sprout::index_t... Indexes>
	struct tuple_element<I, sprout::index_tuple<Indexes...> > {
		static_assert(I < sizeof...(Indexes), "tuple_element<>: index out of range");
	public:
		typedef sprout::index_t type;
	};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_INDEX_TUPLE_TUPLE_HPP
