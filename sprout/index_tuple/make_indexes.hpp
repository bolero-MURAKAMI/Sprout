#ifndef SPROUT_INDEX_TUPLE_MAKE_INDEXES_HPP
#define SPROUT_INDEX_TUPLE_MAKE_INDEXES_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// make_indexes
	//
	template<typename Seq>
	inline SPROUT_CONSTEXPR typename Seq::type
	make_indexes() {
		return typename Seq::type();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_MAKE_INDEXES_HPP
