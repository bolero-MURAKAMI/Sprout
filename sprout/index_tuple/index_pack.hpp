/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INDEX_TUPLE_INDEX_PACK_HPP
#define SPROUT_INDEX_TUPLE_INDEX_PACK_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/index_tuple/integer_pack.hpp>
#include <sprout/index_tuple/enable_make_indexes.hpp>

namespace sprout {
	//
	// index_pack
	// uindex_pack
	//
#if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
	template<typename... Ts>
	using index_pack = sprout::integer_pack<sprout::index_t, Ts...>;

	template<typename... Ts>
	using uindex_pack = sprout::integer_pack<sprout::uindex_t, Ts...>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
	template<typename... Ts>
	struct index_pack
		: public sprout::enable_make_indexes<
			typename sprout::integer_pack<sprout::index_t, Ts...>::type
				::template transfer<sprout::index_tuple<> >
		>
	{};

	template<typename... Ts>
	struct uindex_pack
		: public sprout::enable_make_indexes<
			typename sprout::integer_pack<sprout::uindex_t, Ts...>::type
				::template transfer<sprout::uindex_tuple<> >
		>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_PACK_HPP
