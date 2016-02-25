/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ITERATOR_INDEX_ITERATOR_HPP
#define SPROUT_TYPE_ITERATOR_INDEX_ITERATOR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/void.hpp>

namespace sprout {
	namespace types {
		//
		// index_iterator
		//
		template<typename Tuple, std::ptrdiff_t Index>
		struct index_iterator
			: public sprout::integral_constant<std::ptrdiff_t, Index>
		{
		public:
			typedef typename sprout::types::tuple_element<Index, Tuple>::type type;
			typedef sprout::types::index_iterator<Tuple, Index + 1> next;
			typedef sprout::types::index_iterator<Tuple, Index - 1> prev;
		public:
			template<std::ptrdiff_t Disatnce>
			struct advance {
			public:
				typedef sprout::types::index_iterator<Tuple, Index + Disatnce> type;
			};
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_INDEX_ITERATOR_HPP
