#ifndef SPROUT_TUPLE_INDEXES_HPP
#define SPROUT_TUPLE_INDEXES_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/index_tuple/enable_make_indexes.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_indexes
		//
		template<typename Tuple>
		struct tuple_indexes
			: public sprout::enable_make_indexes<
				sprout::make_index_tuple<sprout::tuples::tuple_size<Tuple>::value>
			>
		{};
	}	// namespace tuples

	//
	// tuple_indexes
	//
	template<typename Tuple>
	struct tuple_indexes
		: public sprout::tuples::tuple_indexes<Tuple>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_INDEXES_HPP
