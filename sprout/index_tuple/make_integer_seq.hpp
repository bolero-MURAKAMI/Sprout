#ifndef SPROUT_INDEX_TUPLE_MAKE_INTEGER_SEQ_HPP
#define SPROUT_INDEX_TUPLE_MAKE_INTEGER_SEQ_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/integer_range.hpp>
#include <sprout/index_tuple/detail/make_indexes_helper.hpp>

namespace sprout {
	//
	// make_integer_seq
	//
	template<typename T, T N>
	struct make_integer_seq
		: public sprout::detail::make_indexes_helper<
			sprout::integer_range<T, 0, N>
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_MAKE_INTEGER_SEQ_HPP
