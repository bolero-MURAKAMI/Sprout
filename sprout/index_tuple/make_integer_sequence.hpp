/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INDEX_TUPLE_MAKE_INTEGER_SEQUENCE_HPP
#define SPROUT_INDEX_TUPLE_MAKE_INTEGER_SEQUENCE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/integer_range.hpp>

namespace sprout {
	//
	// make_integer_sequence
	//
#if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
	template<typename T, T N>
	using make_integer_sequence = sprout::integer_range<T, 0, N>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
	template<typename T, T N>
	struct make_integer_sequence
		: public sprout::integer_range<T, 0, N>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_MAKE_INTEGER_SEQUENCE_HPP
