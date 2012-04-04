#ifndef SPROUT_INDEX_TUPLE_PACK_INDEXES_HPP
#define SPROUT_INDEX_TUPLE_PACK_INDEXES_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/detail/make_indexes_helper.hpp>

namespace sprout {
	//
	// pack_indexes
	//
	template<typename... Args>
	struct pack_indexes
		: public sprout::detail::make_indexes_helper<
			sprout::index_range<0, sizeof...(Args)>
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_PACK_INDEXES_HPP
