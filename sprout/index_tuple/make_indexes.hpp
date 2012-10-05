#ifndef SPROUT_INDEX_TUPLE_MAKE_INDEXES_HPP
#define SPROUT_INDEX_TUPLE_MAKE_INDEXES_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// make_indexes
	//
	template<typename IndexTupleType>
	inline SPROUT_CONSTEXPR typename IndexTupleType::type
	make_indexes() {
		return typename IndexTupleType::type();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_MAKE_INDEXES_HPP
