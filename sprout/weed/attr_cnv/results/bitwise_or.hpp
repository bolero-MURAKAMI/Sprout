/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_ATTR_CNV_RESULTS_BITWISE_OR_HPP
#define SPROUT_WEED_ATTR_CNV_RESULTS_BITWISE_OR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/array/array.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/variant/variant.hpp>
#include <sprout/type_traits/identity.hpp>
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
			namespace results {
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
				>
					: public std::conditional<
						!(sprout::tuples::tuple_size<T>::value < sprout::tuples::tuple_size<U>::value),
						T,
						U
					>
				{};
				// container<V, N> | V -> container<V, N ? N : 1>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_container_and_elem<T, U>::value
					>::type
				>
					: public std::conditional<
						sprout::container_traits<T>::static_size != 0,
						T,
						typename sprout::container_transform_traits<T>::template rebind_size<1>::type
					>
				{};
				// V | container<V, N> -> container<V, N ? N : 1>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_elem_and_container<T, U>::value
					>::type
				>
					: public std::conditional<
						sprout::container_traits<T>::static_size != 0,
						U,
						typename sprout::container_transform_traits<U>::template rebind_size<1>::type
					>
				{};
				// tuple<Vs...> | tuple<Ws...> -> tuple<max(Vs..., Ws...)>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_both_tuple<T, U>::value
					>::type
				>
					: public std::conditional<
						!(sprout::tuples::tuple_size<T>::value < sprout::tuples::tuple_size<U>::value),
						T,
						U
					>
				{};
				// V | V -> V
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_same_elem<T, U>::value
					>::type
				>
					: public sprout::identity<T>
				{};
				// V | W -> variant<V, W>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_different_elem<T, U>::value
					>::type
				>
					: public sprout::identity<sprout::variant<T, U> >
				{};
				// V | unused -> container<V, 1>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_elem_and_unused<T, U>::value
					>::type
				>
					: public std::conditional<
						sprout::weed::traits::is_char_type<T>::value,
						sprout::basic_string<T, 1>,
						sprout::array<T, 1>
					>
				{};
				// unused | V -> container<V, 1>
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_unused_and_elem<T, U>::value
					>::type
				>
					: public std::conditional<
						sprout::weed::traits::is_char_type<U>::value,
						sprout::basic_string<U, 1>,
						sprout::array<U, 1>
					>
				{};
				// unused | unused -> unused
				template<typename T, typename U>
				struct bitwise_or<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_both_unused<T, U>::value
					>::type
				>
					: public sprout::identity<sprout::weed::unused>
				{};
			}	// namespace results
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_RESULTS_BITWISE_OR_HPP
