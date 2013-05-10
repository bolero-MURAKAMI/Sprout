#ifndef SPROUT_INDEX_TUPLE_INTEGER_PACK_HPP
#define SPROUT_INDEX_TUPLE_INTEGER_PACK_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/make_integer_sequence.hpp>

namespace sprout {
	//
	// integer_pack
	//
	template<typename T, typename... Ts>
	struct integer_pack
		: public sprout::make_integer_sequence<T, sizeof...(Ts)>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INTEGER_PACK_HPP
