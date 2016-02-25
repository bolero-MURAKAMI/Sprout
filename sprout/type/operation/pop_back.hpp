/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_POP_BACK_HPP
#define SPROUT_TYPE_OPERATION_POP_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/rebind_types.hpp>

namespace sprout {
	namespace types {
		//
		// pop_back
		//
		template<typename Tuple>
		struct pop_back {
		private:
			template<typename IndexTuple>
			struct apply_impl;
			template<sprout::index_t... Indexes>
			struct apply_impl<sprout::index_tuple<Indexes...> >
				: public sprout::types::apply<
					sprout::types::rebind_types<Tuple>,
					typename sprout::types::tuple_element<Indexes, Tuple>::type...
				>
			{};
		public:
			typedef typename apply_impl<
				typename sprout::make_index_tuple<sprout::types::tuple_size<Tuple>::value - 1>::type
			>::type type;
		};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple>
		using pop_back_t = typename sprout::types::pop_back<Tuple>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_POP_BACK_HPP
