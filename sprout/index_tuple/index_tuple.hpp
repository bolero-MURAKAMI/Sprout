#ifndef SPROUT_INDEX_TUPLE_INDEX_TUPLE_HPP
#define SPROUT_INDEX_TUPLE_INDEX_TUPLE_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	//
	// index_t
	//
	typedef std::ptrdiff_t index_t;

	//
	// index_tuple
	//
	template<sprout::index_t... Indexes>
	struct index_tuple {
	public:
		typedef index_tuple type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_TUPLE_HPP
