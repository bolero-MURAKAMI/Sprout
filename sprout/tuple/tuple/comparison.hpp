/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_COMPARISON_HPP
#define SPROUT_TUPLE_TUPLE_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	namespace tuples {
		//
		// operator==
		// operator<
		// operator!=
		// operator>
		// operator>=
		// operator<=
		//
		namespace detail {
			template<std::size_t CheckEqualSize, std::size_t I, std::size_t J, typename T, typename U>
			struct tuple_compare;
			template<std::size_t I, typename T, typename U>
			struct tuple_compare<0, I, I, T, U> {
			public:
				static SPROUT_CONSTEXPR bool
				eq(T const&, U const&) {
					return true;
				}
				static SPROUT_CONSTEXPR bool
				less(T const&, U const&) {
					return false;
				}
			};
			template<std::size_t I, std::size_t J, typename T, typename U>
			struct tuple_compare<0, I, J, T, U> {
			public:
				static SPROUT_CONSTEXPR bool
				eq(T const& t, U const& u) {
					return (sprout::tuples::get<I>(t) == sprout::tuples::get<I>(u)
						&& sprout::tuples::detail::tuple_compare<0, I + 1, J, T, U>::eq(t, u))
						;
				}
				static SPROUT_CONSTEXPR bool
				less(T const& t, U const& u) {
					return (sprout::tuples::get<I>(t) < sprout::tuples::get<I>(u))
						|| (!(sprout::tuples::get<I>(u) < sprout::tuples::get<I>(t))
							&& sprout::tuples::detail::tuple_compare<0, I + 1, J, T, U>::less(t, u)
							)
						;
				}
			};
		}	// namespace detail
		template<typename... TTypes, typename... UTypes>
		inline SPROUT_CONSTEXPR bool
		operator==(sprout::tuples::tuple<TTypes...> const& lhs, sprout::tuples::tuple<UTypes...> const& rhs) {
			typedef sprout::tuples::tuple<TTypes...> T;
			typedef sprout::tuples::tuple<UTypes...> U;
			return sprout::tuples::detail::tuple_compare<
				sprout::tuples::tuple_size<T>::value - sprout::tuples::tuple_size<U>::value,
				0,
				sprout::tuples::tuple_size<T>::value,
				T,
				U
				>::eq(lhs, rhs);
		}
		template<typename... TTypes, typename... UTypes>
		inline SPROUT_CONSTEXPR bool
		operator<(sprout::tuples::tuple<TTypes...> const& lhs, sprout::tuples::tuple<UTypes...> const& rhs) {
			typedef sprout::tuples::tuple<TTypes...> T;
			typedef sprout::tuples::tuple<UTypes...> U;
			return sprout::tuples::detail::tuple_compare<
				sprout::tuples::tuple_size<T>::value - sprout::tuples::tuple_size<U>::value,
				0,
				sprout::tuples::tuple_size<T>::value,
				T,
				U
				>::less(lhs, rhs);
		}
		template<typename... TTypes, typename... UTypes>
		inline SPROUT_CONSTEXPR bool
		operator!=(sprout::tuples::tuple<TTypes...> const& lhs, sprout::tuples::tuple<UTypes...> const& rhs) {
			return !(lhs == rhs);
		}
		template<typename... TTypes, typename... UTypes>
		inline SPROUT_CONSTEXPR bool
		operator>(sprout::tuples::tuple<TTypes...> const& lhs, sprout::tuples::tuple<UTypes...> const& rhs) {
			return rhs < lhs;
		}
		template<typename... TTypes, typename... UTypes>
		inline SPROUT_CONSTEXPR bool
		operator<=(sprout::tuples::tuple<TTypes...> const& lhs, sprout::tuples::tuple<UTypes...> const& rhs) {
			return !(rhs < lhs);
		}
		template<typename... TTypes, typename... UTypes>
		inline SPROUT_CONSTEXPR bool
		operator>=(sprout::tuples::tuple<TTypes...> const& lhs, sprout::tuples::tuple<UTypes...> const& rhs) {
			return !(lhs < rhs);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_COMPARISON_HPP
