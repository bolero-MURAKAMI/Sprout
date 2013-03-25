#ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_SHIFT_LEFT_HPP
#define SPROUT_WEED_ATTR_CNV_RESULT_OF_SHIFT_LEFT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/array/array.hpp>
#include <sprout/operation/fixed/append_back.hpp>
#include <sprout/operation/fixed/push_back.hpp>
#include <sprout/operation/fixed/push_front.hpp>
#include <sprout/tuple/operation/append_back.hpp>
#include <sprout/tuple/operation/push_back.hpp>
#include <sprout/tuple/operation/push_front.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/traits/type/is_char_type.hpp>
#include <sprout/weed/detail/is_same_container.hpp>
#include <sprout/weed/detail/is_container_and_elem.hpp>
#include <sprout/weed/detail/is_elem_and_container.hpp>
#include <sprout/weed/detail/is_both_tuple.hpp>
#include <sprout/weed/detail/is_tuple_and_elem.hpp>
#include <sprout/weed/detail/is_elem_and_tuple.hpp>
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
				// shift_left
				//
				template<typename T, typename U, typename = void>
				struct shift_left;
				// container<V, N> >> container<V, M> -> container<V, N + M>
				template<typename T, typename U>
				struct shift_left<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_same_container<T, U>::value
					>::type
				>
					: public sprout::fixed::result_of::append_back<T, U>
				{};
				// container<V, N> >> V -> container<V, N + 1>
				template<typename T, typename U>
				struct shift_left<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_container_and_elem<T, U>::value
					>::type
				>
					: public sprout::fixed::result_of::push_back<T, U>
				{};
				// V >> container<V, N> -> container<V, N + 1>
				template<typename T, typename U>
				struct shift_left<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_elem_and_container<T, U>::value
					>::type
				>
					: public sprout::fixed::result_of::push_front<T, U>
				{};
				// tuple<Vs...> >> tuple<Ws...> -> tuple<Vs..., Ws...>
				template<typename T, typename U>
				struct shift_left<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_both_tuple<T, U>::value
					>::type
				>
					: public sprout::tuples::result_of::append_back<T, U>
				{};
				// tuple<Vs...> >> V -> tuple<Vs..., V>
				template<typename T, typename U>
				struct shift_left<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_tuple_and_elem<T, U>::value
					>::type
				>
					: public sprout::tuples::result_of::push_back<T, U>
				{};
				// V >> tuple<Vs...> -> tuple<V, Vs...>
				template<typename T, typename U>
				struct shift_left<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_elem_and_tuple<T, U>::value
					>::type
				>
					: public sprout::tuples::result_of::push_front<T, U>
				{};
				// V >> V -> container<V, 2>
				template<typename T, typename U>
				struct shift_left<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_same_elem<T, U>::value
					>::type
				>
					: public std::conditional<
						sprout::weed::traits::is_char_type<T>::value,
						sprout::basic_string<T, 2>,
						sprout::array<T, 2>
					>
				{};
				// V >> W -> tuple<V, W>
				template<typename T, typename U>
				struct shift_left<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_different_elem<T, U>::value
					>::type
				>
					: public sprout::identity<sprout::tuples::tuple<T, U> >
				{};
				// V >> unused -> V
				template<typename T, typename U>
				struct shift_left<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_elem_and_unused<T, U>::value
					>::type
				>
					: public sprout::identity<T>
				{};
				// unused >> V -> V
				template<typename T, typename U>
				struct shift_left<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_unused_and_elem<T, U>::value
					>::type
				>
					: public sprout::identity<U>
				{};
				// unused >> unused -> unused
				template<typename T, typename U>
				struct shift_left<
					T,
					U,
					typename std::enable_if<
						sprout::weed::detail::is_both_unused<T, U>::value
					>::type
				>
					: public sprout::identity<sprout::weed::unused>
				{};
			}	// namespace result_of
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_SHIFT_LEFT_HPP
