/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_TUPLE_ACCESS_TRAITS_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_ACCESS_TRAITS_HPP

#include <utility>
#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple/tuple_traits.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	template<std::size_t I>
	sprout::not_found_via_adl tuple_get(...);
}	// namespace sprout_adl

namespace sprout_tuple_detail {
	template<std::size_t I, typename T>
	inline SPROUT_CONSTEXPR decltype(std::get<I>(std::declval<T&>()))
	tuple_get(T& t)
	SPROUT_NOEXCEPT_IF_EXPR(std::get<I>(std::declval<T&>()))
	{
		return std::get<I>(t);
	}
	template<std::size_t I, typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<T>::value && !std::is_volatile<T>::value && !std::is_reference<T>::value,
		decltype(sprout::move(std::get<I>(std::declval<T&&>())))
	>::type
	tuple_get(T&& t)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::move(std::get<I>(std::declval<T&&>())))
	{
		return sprout::move(std::get<I>(t));
	}
	template<std::size_t I, typename T>
	inline SPROUT_CONSTEXPR decltype(std::get<I>(std::declval<T const&>()))
	tuple_get(T const& t)
	SPROUT_NOEXCEPT_IF_EXPR(std::get<I>(std::declval<T const&>()))
	{
		return std::get<I>(t);
	}
}	// namespace sprout_tuple_detail

namespace sprout {
	namespace tuples {
		//
		// tuple_access_traits
		//
		template<typename Tuple>
		struct tuple_access_traits {
		public:
			template<std::size_t I>
			static SPROUT_CONSTEXPR typename sprout::tuples::tuple_traits<Tuple>::template lvalue_reference<I>::type
			tuple_get(Tuple& t) SPROUT_NOEXCEPT {
				using sprout_tuple_detail::tuple_get;
				using sprout_adl::tuple_get;
				return tuple_get<I>(t);
			}
			template<std::size_t I>
			static SPROUT_CONSTEXPR typename sprout::tuples::tuple_traits<Tuple>::template rvalue_reference<I>::type
			tuple_get(Tuple&& t) SPROUT_NOEXCEPT {
				using sprout_tuple_detail::tuple_get;
				using sprout_adl::tuple_get;
				return tuple_get<I>(sprout::move(t));
			}
			template<std::size_t I>
			static SPROUT_CONSTEXPR typename sprout::tuples::tuple_traits<Tuple const>::template lvalue_reference<I>::type
			tuple_get(Tuple const& t) SPROUT_NOEXCEPT {
				using sprout_tuple_detail::tuple_get;
				using sprout_adl::tuple_get;
				return tuple_get<I>(t);
			}
		};
		template<typename Tuple>
		struct tuple_access_traits<Tuple const> {
		public:
			template<std::size_t I>
			static SPROUT_CONSTEXPR typename sprout::tuples::tuple_traits<Tuple const>::template lvalue_reference<I>::type
			tuple_get(Tuple const& t) SPROUT_NOEXCEPT {
				return sprout::tuples::tuple_access_traits<Tuple>::template tuple_get<I>(t);
			}
		};
	}	// namespace tuples

	using sprout::tuples::tuple_access_traits;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_ACCESS_TRAITS_HPP
