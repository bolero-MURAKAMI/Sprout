/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_INDEX_TUPLE_HPP
#define SPROUT_TYPE_INDEX_TUPLE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/integer_sequence.hpp>
#include <sprout/type/rebind_types.hpp>

namespace sprout {
	namespace types {
		//
		// rebind_types
		//
		template<typename T, T... Is>
		struct rebind_types<sprout::integer_sequence<T, Is...> > {
		public:
			template<typename... Types>
			struct apply {
			public:
				typedef sprout::integer_sequence<T, Types::value...> type;
			};
		};

#if !(SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES))
		//
		// rebind_types
		//
		template<sprout::index_t... Is>
		struct rebind_types<sprout::index_tuple<Is...> > {
		public:
			template<typename... Types>
			struct apply {
			public:
				typedef sprout::index_tuple<Types::value...> type;
			};
		};
		template<sprout::uindex_t... Is>
		struct rebind_types<sprout::uindex_tuple<Is...> > {
		public:
			template<typename... Types>
			struct apply {
			public:
				typedef sprout::uindex_tuple<Types::value...> type;
			};
		};
#endif	// #if !(SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES))
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_INDEX_TUPLE_HPP
