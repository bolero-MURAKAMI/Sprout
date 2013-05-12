#ifndef SPROUT_INDEX_TUPLE_INDEX_N_HPP
#define SPROUT_INDEX_TUPLE_INDEX_N_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/index_tuple/integer_n.hpp>

namespace sprout {
	//
	// index_n
	// uindex_n
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<sprout::index_t I, std::size_t N>
	using index_n = sprout::integer_n<sprout::index_t, I, N>;

	template<sprout::uindex_t I, std::size_t N>
	using uindex_n = sprout::integer_n<sprout::uindex_t, I, N>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<sprout::index_t I, std::size_t N>
	struct index_n
		: public typename sprout::integer_n<sprout::index_t, I, N>::type
			::template transfer<sprout::index_tuple<> >
	{};

	template<sprout::uindex_t I, std::size_t N>
	struct uindex_n
		: public typename sprout::integer_n<sprout::uindex_t, I, N>::type
			::template transfer<sprout::uindex_tuple<> >
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_N_HPP
