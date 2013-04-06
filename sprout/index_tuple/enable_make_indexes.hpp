#ifndef SPROUT_INDEX_TUPLE_ENABLE_MAKE_INDEXES_HPP
#define SPROUT_INDEX_TUPLE_ENABLE_MAKE_INDEXES_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// enable_make_indexes
	//
	template<typename IndexTupleType>
	struct enable_make_indexes
		: public IndexTupleType::type
	{
	public:
		typedef typename IndexTupleType::type type;
	public:
		static SPROUT_CONSTEXPR type make() {
			return type();
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_ENABLE_MAKE_INDEXES_HPP
