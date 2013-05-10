#ifndef SPROUT_INDEX_TUPLE_MAKE_INTEGER_SEQUENCE_HPP
#define SPROUT_INDEX_TUPLE_MAKE_INTEGER_SEQUENCE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/integer_range.hpp>
#include <sprout/index_tuple/enable_make_indexes.hpp>

namespace sprout {
	//
	// make_integer_sequence
	//
	template<typename T, T N>
	struct make_integer_sequence
		: public sprout::enable_make_indexes<
			sprout::integer_range<T, 0, N>
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_MAKE_INTEGER_SEQUENCE_HPP
