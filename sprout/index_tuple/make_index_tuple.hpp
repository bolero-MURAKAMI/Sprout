#ifndef SPROUT_INDEX_TUPLE_MAKE_INDEX_TUPLE_HPP
#define SPROUT_INDEX_TUPLE_MAKE_INDEX_TUPLE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/index_tuple/make_integer_seq.hpp>
#include <sprout/index_tuple/detail/make_indexes_helper.hpp>

namespace sprout {
	//
	// make_index_tuple
	//
	template<sprout::index_t N>
	struct make_index_tuple
		: public sprout::detail::make_indexes_helper<
			typename sprout::make_integer_seq<sprout::index_t, N>::type
				::template transfer<sprout::index_tuple<> >::type
		>
	{};
	//
	// make_uindex_tuple
	//
	template<sprout::uindex_t N>
	struct make_uindex_tuple
		: public sprout::detail::make_indexes_helper<
			typename sprout::make_integer_seq<sprout::uindex_t, N>::type
				::template transfer<sprout::uindex_tuple<> >::type
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_MAKE_INDEX_TUPLE_HPP
