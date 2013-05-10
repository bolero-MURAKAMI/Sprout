#ifndef SPROUT_INDEX_TUPLE_INDEX_PACK_HPP
#define SPROUT_INDEX_TUPLE_INDEX_PACK_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/index_tuple/integer_pack.hpp>
#include <sprout/index_tuple/enable_make_indexes.hpp>

namespace sprout {
	//
	// index_pack
	//
	template<typename... Ts>
	struct index_pack
		: public sprout::enable_make_indexes<
			typename sprout::integer_pack<sprout::index_t, Ts...>::type
				::template transfer<sprout::index_tuple<> >
		>
	{};
	//
	// uindex_pack
	//
	template<typename... Ts>
	struct uindex_pack
		: public sprout::enable_make_indexes<
			typename sprout::integer_pack<sprout::uindex_t, Ts...>::type
				::template transfer<sprout::uindex_tuple<> >
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_PACK_HPP
