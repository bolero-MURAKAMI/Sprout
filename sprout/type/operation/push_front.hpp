/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_PUSH_FRONT_HPP
#define SPROUT_TYPE_OPERATION_PUSH_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/rebind_types.hpp>
#include <sprout/tuple/indexes.hpp>

namespace sprout {
	namespace types {
		//
		// push_front
		//
		template<typename Tuple, typename... Ts>
		struct push_front {
		private:
			template<typename IndexTuple>
			struct apply_impl;
			template<sprout::index_t... Indexes>
			struct apply_impl<sprout::index_tuple<Indexes...> >
				: public sprout::types::rebind_types<
					Tuple
				>::template apply<
					Ts...,
					typename sprout::types::tuple_element<Indexes, Tuple>::type...
				>
			{};
		public:
			typedef typename apply_impl<
				typename sprout::tuple_indexes<Tuple>::type
			>::type type;
		};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename... Ts>
		using push_front_t = typename sprout::types::push_front<Tuple, Ts...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_PUSH_FRONT_HPP
