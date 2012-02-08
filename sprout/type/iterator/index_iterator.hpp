#ifndef SPROUT_TYPE_ITERATOR_INDEX_ITERATOR_HPP
#define SPROUT_TYPE_ITERATOR_INDEX_ITERATOR_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/void.hpp>

namespace sprout {
	namespace types {
		template<typename Tuple, std::ptrdiff_t Index>
		struct index_iterator;

		namespace detail {
			//
			// index_iterator_impl
			//
			template<typename Tuple, std::ptrdiff_t Index, typename = void>
			struct index_iterator_impl;
			template<typename Tuple, std::ptrdiff_t Index>
			struct index_iterator_impl<
				Tuple,
				Index,
				typename std::enable_if<
					sprout::types::tuple_size<Tuple>::value == 0
					|| (Index < 0)
					|| (Index > sprout::types::tuple_size<Tuple>::value)
				>::type
			> {
			public:
				typedef sprout::types::void_ type;
				typedef sprout::types::void_ next;
				typedef sprout::types::void_ prev;
			};
			template<typename Tuple, std::ptrdiff_t Index>
			struct index_iterator_impl<
				Tuple,
				Index,
				typename std::enable_if<
					sprout::types::tuple_size<Tuple>::value != 0
					&& Index == 0
				>::type
			> {
			public:
				typedef typename sprout::types::tuple_element<Index, Tuple>::type type;
				typedef sprout::types::index_iterator<Tuple, Index + 1> next;
				typedef sprout::types::void_ prev;
			};
			template<typename Tuple, std::ptrdiff_t Index>
			struct index_iterator_impl<
				Tuple,
				Index,
				typename std::enable_if<
					sprout::types::tuple_size<Tuple>::value != 0
					&& Index == sprout::types::tuple_size<Tuple>::value
				>::type
			> {
			public:
				typedef sprout::types::void_ type;
				typedef sprout::types::void_ next;
				typedef sprout::types::index_iterator<Tuple, sprout::types::tuple_size<Tuple>::value - 1> prev;
			};
			template<typename Tuple, std::ptrdiff_t Index>
			struct index_iterator_impl<
				Tuple,
				Index,
				typename std::enable_if<
					sprout::types::tuple_size<Tuple>::value != 0
					&& (Index > 0)
					&& (Index < sprout::types::tuple_size<Tuple>::value)
				>::type
			> {
			public:
				typedef typename sprout::types::tuple_element<Index, Tuple>::type type;
				typedef sprout::types::index_iterator<Tuple, Index + 1> next;
				typedef sprout::types::index_iterator<Tuple, Index - 1> prev;
			};
		}	// namespace detail
		//
		// index_iterator
		//
		template<typename Tuple, std::ptrdiff_t Index>
		struct index_iterator
			: public sprout::types::detail::index_iterator_impl<Tuple, Index>
			, public std::integral_constant<std::ptrdiff_t, Index>
		{
		public:
			typedef typename sprout::types::detail::index_iterator_impl<Tuple, Index>::type type;
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_INDEX_ITERATOR_HPP
