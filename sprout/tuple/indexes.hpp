#ifndef SPROUT_TUPLE_INDEXES_HPP
#define SPROUT_TUPLE_INDEXES_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/tuple/tuple.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_indexes
		//
		template<typename Tuple>
		struct tuple_indexes
			: public sprout::detail::make_index_tuple_helper<
				sprout::index_range<0, sprout::tuples::tuple_size<Tuple>::value>
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
