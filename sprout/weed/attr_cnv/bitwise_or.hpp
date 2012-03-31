#ifndef SPROUT_WEED_ATTR_CNV_BITWISE_OR_HPP
#define SPROUT_WEED_ATTR_CNV_BITWISE_OR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/make.hpp>
#include <sprout/operation/fixed/realign_to.hpp>
#include <sprout/tuple/algorithm/copy.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/traits/type/is_container.hpp>
#include <sprout/weed/detail/is_same_container.hpp>
#include <sprout/weed/detail/is_container_and_elem.hpp>
#include <sprout/weed/detail/is_elem_and_container.hpp>
#include <sprout/weed/detail/is_both_tuple.hpp>
#include <sprout/weed/detail/is_same_elem.hpp>
#include <sprout/weed/detail/is_different_elem.hpp>
#include <sprout/weed/detail/is_elem_and_unused.hpp>
#include <sprout/weed/detail/is_unused_and_elem.hpp>
#include <sprout/weed/detail/is_both_unused.hpp>
#include <sprout/weed/attr_cnv/result_of/bitwise_or.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			//
			// bitwise_or
			//
			// container<V, N> | container<V, M> -> container<V, max(N, M)>
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_same_container<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				typedef typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type type;
				return sprout::fixed::realign_to<type>(x);
			}
			// container<V, N> | V -> container<V, N ? N : 1>
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_container_and_elem<T, U>::value
				&& sprout::weed::traits::is_container<X>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				typedef typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type type;
				return sprout::fixed::realign_to<type>(x);
			}
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_container_and_elem<T, U>::value
				&& !sprout::weed::traits::is_container<X>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				typedef typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type type;
				return sprout::make<type>(x);
			}
			// V | container<V, N> -> container<V, N ? N : 1>
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_elem_and_container<T, U>::value
				&& sprout::weed::traits::is_container<X>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				typedef typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type type;
				return sprout::fixed::realign_to<type>(x);
			}
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_elem_and_container<T, U>::value
				&& !sprout::weed::traits::is_container<X>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				typedef typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type type;
				return sprout::make<type>(x);
			}
			// tuple<Vs...> | tuple<Ws...> -> tuple<max(Vs..., Ws...)>
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_both_tuple<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				typedef typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type type;
				return sprout::tuples::copy(type(), x);
			}
			// V | V -> V
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_same_elem<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				return x;
			}
			// V | W -> variant<V, W>
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_different_elem<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				return typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type(x);
			}
			// V | unused -> container<V, 1>
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_elem_and_unused<T, U>::value
				&& !sprout::weed::traits::is_unused<X>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				typedef typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type type;
				return sprout::make<type>(x);
			}
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_elem_and_unused<T, U>::value
				&& sprout::weed::traits::is_unused<X>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				typedef typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type type;
				return sprout::make<type>();
			}
			// unused | V -> container<V, 1>
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_unused_and_elem<T, U>::value
				&& !sprout::weed::traits::is_unused<X>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				typedef typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type type;
				return sprout::make<type>(x);
			}
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_unused_and_elem<T, U>::value
				&& sprout::weed::traits::is_unused<X>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				typedef typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type type;
				return sprout::make<type>();
			}
			// unused >> unused -> unused
			template<typename T, typename U, typename X>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::detail::is_both_unused<T, U>::value,
				typename sprout::weed::attr_cnv::result_of::bitwise_or<T, U>::type
			>::type bitwise_or(X const& x) {
				return sprout::weed::unused();
			}
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_BITWISE_OR_HPP
