/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INDEX_TUPLE_INDEX_RANGE_HPP
#define SPROUT_INDEX_TUPLE_INDEX_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/index_tuple/integer_range.hpp>

namespace sprout {
	//
	// index_range
	// uindex_range
	//
// !!! for GCC 7.0.0 or later
//#if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
#if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES) && !SPROUT_GCC_OR_LATER(7, 0, 0)
	template<
		sprout::index_t First, sprout::index_t Last,
		typename std::make_signed<sprout::index_t>::type Step = sprout::detail::integer_range_default_step<sprout::index_t, First, Last>::value
	>
	using index_range = sprout::integer_range<sprout::index_t, First, Last, Step>;

	template<
		sprout::uindex_t First, sprout::uindex_t Last,
		typename std::make_signed<sprout::uindex_t>::type Step = sprout::detail::integer_range_default_step<sprout::uindex_t, First, Last>::value
	>
	using uindex_range = sprout::integer_range<sprout::uindex_t, First, Last, Step>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
	template<
		sprout::index_t First, sprout::index_t Last,
		typename std::make_signed<sprout::index_t>::type Step = sprout::detail::integer_range_default_step<sprout::index_t, First, Last>::value
	>
	struct index_range
		: public sprout::integer_range<sprout::index_t, First, Last, Step>::type
			::template transfer<sprout::index_tuple<> >
	{};

	template<
		sprout::uindex_t First, sprout::uindex_t Last,
		typename std::make_signed<sprout::uindex_t>::type Step = sprout::detail::integer_range_default_step<sprout::uindex_t, First, Last>::value
	>
	struct uindex_range
		: public sprout::integer_range<sprout::uindex_t, First, Last, Step>::type
			::template transfer<sprout::uindex_tuple<> >
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_RANGE_HPP
