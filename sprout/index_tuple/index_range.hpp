#ifndef SPROUT_INDEX_TUPLE_INDEX_RANGE_HPP
#define SPROUT_INDEX_TUPLE_INDEX_RANGE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/index_tuple/integer_range.hpp>
#include <sprout/index_tuple/detail/make_indexes_helper.hpp>

namespace sprout {
	//
	// index_range
	//
	template<sprout::index_t First, sprout::index_t Last, std::ptrdiff_t Step = 1>
	struct index_range
		: public sprout::detail::make_indexes_helper<
			typename sprout::integer_range<sprout::index_t, First, Last, Step>::type
				::template transfer<sprout::index_tuple<> >::type
		>
	{};
	//
	// uindex_range
	//
	template<sprout::uindex_t First, sprout::uindex_t Last, std::ptrdiff_t Step = 1>
	struct uindex_range
		: public sprout::detail::make_indexes_helper<
			typename sprout::integer_range<sprout::uindex_t, First, Last, Step>::type
				::template transfer<sprout::uindex_tuple<> >::type
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_RANGE_HPP
