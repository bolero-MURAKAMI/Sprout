#ifndef SPROUT_WEED_ATTR_CNV_SHIFT_LEFT_HPP
#define SPROUT_WEED_ATTR_CNV_SHIFT_LEFT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/operation/fixed/append_back.hpp>
#include <sprout/operation/fixed/push_back.hpp>
#include <sprout/operation/fixed/push_front.hpp>
#include <sprout/tuple/operation/append_back.hpp>
#include <sprout/tuple/operation/push_back.hpp>
#include <sprout/tuple/operation/push_front.hpp>
#include <sprout/weed/unused.hpp>
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
#include <sprout/weed/attr_cnv/result_of/shift_left.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			//
			// shift_left
			//
			// container<V, N> >> container<V, M> -> container<V, N + M>
			template<typename T, typename U>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::detail::is_same_container<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type
			>::type shift_left(T const& t, U const& u) {
				return sprout::fixed::append_back(t, u);
			}
			// container<V, N> >> V -> container<V, N + 1>
			template<typename T, typename U>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::detail::is_container_and_elem<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type
			>::type shift_left(T const& t, U const& u) {
				return sprout::fixed::push_back(t, u);
			}
			// V >> container<V, N> -> container<V, N + 1>
			template<typename T, typename U>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::detail::is_elem_and_container<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type
			>::type shift_left(T const& t, U const& u) {
				return sprout::fixed::push_front(u, t);
			}
			// tuple<Vs...> >> tuple<Ws...> -> tuple<Vs..., Ws...>
			template<typename T, typename U>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::detail::is_both_tuple<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type
			>::type shift_left(T const& t, U const& u) {
				return sprout::tuples::append_back(t, u);
			}
			// tuple<Vs...> >> V -> tuple<Vs..., V>
			template<typename T, typename U>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::detail::is_tuple_and_elem<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type
			>::type shift_left(T const& t, U const& u) {
				return sprout::tuples::push_back(t, u);
			}
			// V >> tuple<Vs...> -> tuple<V, Vs...>
			template<typename T, typename U>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::detail::is_elem_and_tuple<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type
			>::type shift_left(T const& t, U const& u) {
				return sprout::tuples::push_front(u, t);
			}
			// V >> V -> container<V, 2>
			template<typename T, typename U>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::detail::is_same_elem<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type
			>::type shift_left(T const& t, U const& u) {
				typedef typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type type;
				return sprout::make<type>(t, u);
			}
			// V >> W -> tuple<V, W>
			template<typename T, typename U>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::detail::is_different_elem<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type
			>::type shift_left(T const& t, U const& u) {
				return typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type(t, u);
			}
			// V >> unused -> V
			template<typename T, typename U>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::detail::is_elem_and_unused<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type
			>::type shift_left(T const& t, U const& u) {
				return t;
			}
			// unused >> V -> V
			template<typename T, typename U>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::detail::is_unused_and_elem<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type
			>::type shift_left(T const& t, U const& u) {
				return u;
			}
			// unused >> unused -> unused
			template<typename T, typename U>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::detail::is_both_unused<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::shift_left<T, U>::type
			>::type shift_left(T const& t, U const& u) {
				return sprout::weed::unused();
			}
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_SHIFT_LEFT_HPP
