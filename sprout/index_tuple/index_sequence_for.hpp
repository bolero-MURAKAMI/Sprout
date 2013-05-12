#ifndef SPROUT_INDEX_TUPLE_INDEX_SEQUENCE_FOR_HPP
#define SPROUT_INDEX_TUPLE_INDEX_SEQUENCE_FOR_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_pack.hpp>

namespace sprout {
	//
	// index_sequence_for
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename... Ts>
	using index_sequence_for = sprout::uindex_pack<Ts...>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename... Ts>
	struct index_sequence_for
		: public sprout::uindex_pack<Ts...>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_SEQUENCE_FOR_HPP
