#ifndef SPROUT_INDEX_TUPLE_MAKE_INDEX_SEQUENCE_HPP
#define SPROUT_INDEX_TUPLE_MAKE_INDEX_SEQUENCE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/index_tuple/make_index_tuple.hpp>

namespace sprout {
	//
	// make_index_sequence
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<sprout::uindex_t N>
	using make_index_sequence = sprout::make_uindex_tuple<N>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<sprout::uindex_t N>
	struct make_index_sequence
		: public sprout::make_uindex_tuple<N>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_MAKE_INDEX_SEQUENCE_HPP
