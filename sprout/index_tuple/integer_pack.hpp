/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INDEX_TUPLE_INTEGER_PACK_HPP
#define SPROUT_INDEX_TUPLE_INTEGER_PACK_HPP

#include <sprout/config.hpp>
#include <sprout/detail/sizeof.hpp>
#include <sprout/index_tuple/make_integer_sequence.hpp>

namespace sprout {
	//
	// integer_pack
	//
#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename... Ts>
	using integer_pack = sprout::make_integer_sequence<T, sprout::detail::sizeof_pack<Ts...>::value>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename... Ts>
	struct integer_pack
		: public sprout::make_integer_sequence<T, sizeof...(Ts)>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INTEGER_PACK_HPP
