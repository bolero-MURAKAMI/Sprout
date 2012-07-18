#ifndef SPROUT_TYPE_ITERATOR_INDEX_ITERATOR_HPP
#define SPROUT_TYPE_ITERATOR_INDEX_ITERATOR_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/void.hpp>

namespace sprout {
	namespace types {
		//
		// index_iterator
		//
		template<typename Tuple, std::ptrdiff_t Index>
		struct index_iterator
			: public std::integral_constant<std::ptrdiff_t, Index>
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
