#ifndef SPROUT_INDEX_TUPLE_INDEX_TUPLE_HPP
#define SPROUT_INDEX_TUPLE_INDEX_TUPLE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple/integer_seq.hpp>

namespace sprout {
	//
	// index_t
	// index_tuple
	//
	typedef std::ptrdiff_t index_t;
	template<sprout::index_t... Indexes>
	struct index_tuple
		: public sprout::integer_seq<sprout::index_t, Indexes...>
	{
	public:
		typedef index_tuple type;
		template<sprout::index_t... J>
		struct rebind
			: public index_tuple<J...>
		{};
	};

	//
	// uindex_t
	// uindex_tuple
	//
	typedef std::size_t uindex_t;
	template<sprout::uindex_t... Indexes>
	struct uindex_tuple
		: public sprout::integer_seq<sprout::uindex_t, Indexes...>
	{
	public:
		typedef uindex_tuple type;
		template<sprout::uindex_t... J>
		struct rebind
			: public uindex_tuple<J...>
		{};
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_TUPLE_HPP
