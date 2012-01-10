#ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_BITWISE_OR_HPP
#define SPROUT_WEED_ATTR_CNV_RESULT_OF_BITWISE_OR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/array.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/variant/variant.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/traits/type/is_char_type.hpp>
#include <sprout/weed/detail/is_same_container.hpp>
#include <sprout/weed/detail/is_container_and_elem.hpp>
#include <sprout/weed/detail/is_elem_and_container.hpp>
#include <sprout/weed/detail/is_both_tuple.hpp>
#include <sprout/weed/detail/is_same_elem.hpp>
#include <sprout/weed/detail/is_different_elem.hpp>
#include <sprout/weed/detail/is_elem_and_unused.hpp>
#include <sprout/weed/detail/is_unused_and_elem.hpp>
#include <sprout/weed/detail/is_both_unused.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			namespace result_of {
				//
				// bitwise_or
				//
				template<typename T, typename U, typename = void>
				struct bitwise_or;
				// container<V, N> | container<V, M> -> container<V, max(N, M)>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_same_container<T, U>::value
					>::type
				> {
				public:
					typedef typename std::conditional<
						!(sprout::tuples::tuple_size<T>::value < sprout::tuples::tuple_size<U>::value),
						T,
						U
					>::type type;
				};
				// container<V, N> | V -> container<V, N ? N : 1>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_container_and_elem<T, U>::value
					>::type
				> {
				public:
					typedef typename std::conditional<
						sprout::fixed_container_traits<T>::fixed_size != 0,
						T,
						typename sprout::rebind_fixed_size<T>::template apply<1>::type
					>::type type;
				};
				// V | container<V, N> -> container<V, N ? N : 1>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_elem_and_container<T, U>::value
					>::type
				> {
				public:
					typedef typename std::conditional<
						sprout::fixed_container_traits<T>::fixed_size != 0,
						U,
						typename sprout::rebind_fixed_size<U>::template apply<1>::type
					>::type type;
				};
				// tuple<Vs...> | tuple<Ws...> -> tuple<max(Vs..., Ws...)>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_both_tuple<T, U>::value
					>::type
				> {
				public:
					typedef typename std::conditional<
						!(sprout::tuples::tuple_size<T>::value < sprout::tuples::tuple_size<U>::value),
						T,
						U
					>::type type;
				};
				// V | V -> V
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_same_elem<T, U>::value
					>::type
				> {
				public:
					typedef T type;
				};
				// V | W -> variant<V, W>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_different_elem<T, U>::value
					>::type
				> {
				public:
					typedef sprout::variant<T, U> type;
				};
				// V | unused -> container<V, 1>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_elem_and_unused<T, U>::value
					>::type
				> {
				public:
					typedef typename std::conditional<
						sprout::weed::traits::is_char_type<T>::value,
						sprout::basic_string<T, 1>,
						sprout::array<T, 1>
					>::type type;
				};
				// unused | V -> container<V, 1>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_unused_and_elem<T, U>::value
					>::type
				> {
				public:
					typedef typename std::conditional<
						sprout::weed::traits::is_char_type<U>::value,
						sprout::basic_string<U, 1>,
						sprout::array<U, 1>
					>::type type;
				};
				// unused | unused -> unused
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_both_unused<T, U>::value
					>::type
				> {
				public:
					typedef sprout::weed::unused type;
				};
			}	// namespace result_of
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_BITWISE_OR_HPP
