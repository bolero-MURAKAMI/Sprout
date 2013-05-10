#ifndef SPROUT_INDEX_TUPLE_MAKE_INDEX_SEQUENCE_HPP
#define SPROUT_INDEX_TUPLE_MAKE_INDEX_SEQUENCE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/index_tuple/make_index_tuple.hpp>

namespace sprout {
	//
	// make_index_sequence
	//
	template<sprout::uindex_t N>
	struct make_index_sequence
		: public sprout::make_uindex_tuple<N>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_MAKE_INDEX_SEQUENCE_HPP
