/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INDEX_TUPLE_INDEX_SEQUENCE_HPP
#define SPROUT_INDEX_TUPLE_INDEX_SEQUENCE_HPP

#include <sprout/config.hpp>
#if SPROUT_USE_TEMPLATE_ALIASES
#	include <sprout/index_tuple/index_tuple.hpp>
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

namespace sprout {
#if SPROUT_USE_TEMPLATE_ALIASES
	//
	// index_sequence
	//
	template<sprout::uindex_t... Indexes>
	using index_sequence = sprout::uindex_tuple<Indexes...>;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_SEQUENCE_HPP
