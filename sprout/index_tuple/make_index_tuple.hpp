/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INDEX_TUPLE_MAKE_INDEX_TUPLE_HPP
#define SPROUT_INDEX_TUPLE_MAKE_INDEX_TUPLE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/index_tuple/make_integer_sequence.hpp>
#include <sprout/index_tuple/enable_make_indexes.hpp>

namespace sprout {
	//
	// make_index_tuple
	// make_uindex_tuple
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<sprout::index_t N>
	using make_index_tuple = sprout::make_integer_sequence<sprout::index_t, N>;

	template<sprout::uindex_t N>
	using make_uindex_tuple = sprout::make_integer_sequence<sprout::uindex_t, N>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<sprout::index_t N>
	struct make_index_tuple
		: public sprout::enable_make_indexes<
			typename sprout::make_integer_sequence<sprout::index_t, N>::type
				::template transfer<sprout::index_tuple<> >::type
		>
	{};

	template<sprout::uindex_t N>
	struct make_uindex_tuple
		: public sprout::enable_make_indexes<
			typename sprout::make_integer_sequence<sprout::uindex_t, N>::type
				::template transfer<sprout::uindex_tuple<> >::type
		>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_MAKE_INDEX_TUPLE_HPP
