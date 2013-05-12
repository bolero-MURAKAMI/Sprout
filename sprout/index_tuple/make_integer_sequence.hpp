#ifndef SPROUT_INDEX_TUPLE_MAKE_INTEGER_SEQUENCE_HPP
#define SPROUT_INDEX_TUPLE_MAKE_INTEGER_SEQUENCE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/integer_range.hpp>

namespace sprout {
	//
	// make_integer_sequence
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, T N>
	using make_integer_sequence = sprout::integer_range<T, 0, N>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, T N>
	struct make_integer_sequence
		: public sprout::integer_range<T, 0, N>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_MAKE_INTEGER_SEQUENCE_HPP
