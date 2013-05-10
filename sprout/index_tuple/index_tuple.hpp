#ifndef SPROUT_INDEX_TUPLE_INDEX_TUPLE_HPP
#define SPROUT_INDEX_TUPLE_INDEX_TUPLE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_t.hpp>
#include <sprout/index_tuple/integer_sequence.hpp>

namespace sprout {
	//
	// index_tuple
	// uindex_tuple
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<sprout::index_t... Indexes>
	using index_tuple = sprout::integer_sequence<sprout::index_t, Indexes...>;

	template<sprout::uindex_t... Indexes>
	using uindex_tuple = sprout::integer_sequence<sprout::uindex_t, Indexes...>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<sprout::index_t... Indexes>
	struct index_tuple
		: public sprout::integer_sequence<sprout::index_t, Indexes...>
	{
	public:
		typedef index_tuple type;
		template<sprout::index_t... J>
		struct rebind
			: public index_tuple<J...>
		{};
	};

	template<sprout::uindex_t... Indexes>
	struct uindex_tuple
		: public sprout::integer_sequence<sprout::uindex_t, Indexes...>
	{
	public:
		typedef uindex_tuple type;
		template<sprout::uindex_t... J>
		struct rebind
			: public uindex_tuple<J...>
		{};
	};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_TUPLE_HPP
