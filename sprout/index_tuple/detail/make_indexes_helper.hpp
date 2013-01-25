#ifndef SPROUT_INDEX_TUPLE_DETAIL_MAKE_INDEXES_HELPER_HPP
#define SPROUT_INDEX_TUPLE_DETAIL_MAKE_INDEXES_HELPER_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename IndexTupleType>
		struct make_indexes_helper
			: public IndexTupleType::type
		{
		public:
			typedef typename IndexTupleType::type type;
		public:
			static SPROUT_CONSTEXPR type make() {
				return type();
			}
		};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_DETAIL_MAKE_INDEXES_HELPER_HPP
