#ifndef SPROUT_INDEX_TUPLE_INDEX_RANGE_HPP
#define SPROUT_INDEX_TUPLE_INDEX_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/index_tuple/integer_range.hpp>
#include <sprout/index_tuple/detail/make_indexes_helper.hpp>

namespace sprout {
	//
	// index_range
	//
	template<
		sprout::index_t First, sprout::index_t Last,
		typename std::make_signed<sprout::index_t>::type Step = sprout::detail::integer_range_default_step<sprout::index_t, First, Last>::value
	>
	struct index_range
		: public sprout::detail::make_indexes_helper<
			typename sprout::integer_range<sprout::index_t, First, Last, Step>::type
				::template transfer<sprout::index_tuple<> >::type
		>
	{};
	//
	// uindex_range
	//
	template<
		sprout::uindex_t First, sprout::uindex_t Last,
		typename std::make_signed<sprout::uindex_t>::type Step = sprout::detail::integer_range_default_step<sprout::uindex_t, First, Last>::value
	>
	struct uindex_range
		: public sprout::detail::make_indexes_helper<
			typename sprout::integer_range<sprout::uindex_t, First, Last, Step>::type
				::template transfer<sprout::uindex_tuple<> >::type
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_RANGE_HPP
