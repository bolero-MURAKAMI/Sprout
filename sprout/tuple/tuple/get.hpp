/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_GET_HPP
#define SPROUT_TUPLE_TUPLE_GET_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/tuple_size.hpp>
#include <sprout/tuple/tuple/tuple_element.hpp>
#include <sprout/tuple/tuple/tuple_traits.hpp>
#include <sprout/tuple/tuple/tuple_access_traits.hpp>
#include <sprout/type/algorithm/find_index.hpp>
#include <sprout/type/algorithm/count.hpp>
#include <sprout/type_traits/remove_cvref.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_get
		//
		template<std::size_t I, typename... Types>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type&
		tuple_get(sprout::tuples::tuple<Types...>& t) SPROUT_NOEXCEPT {
			return sprout::tuples::detail::tuple_access<Types...>::template get<I>(t);
		}
		template<std::size_t I, typename... Types>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type&&
		tuple_get(sprout::tuples::tuple<Types...>&& t) SPROUT_NOEXCEPT {
			return sprout::tuples::detail::tuple_access<Types...>::template get<I>(sprout::move(t));
		}
		template<std::size_t I, typename... Types>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type const&
		tuple_get(sprout::tuples::tuple<Types...> const& t) SPROUT_NOEXCEPT {
			return sprout::tuples::detail::tuple_access<Types...>::template get<I>(t);
		}
	}	// namespace tuples

	using sprout::tuples::tuple_get;
}	// namespace sprout

namespace sprout {
	namespace tuples {
		//
		// get
		//
		//	effect:
		//		sprout::tuples::tuple_access_traits<typename std::remove_reference<T>::type>::template tuple_get<I>(t)
		//		[default]
		//			ADL callable tuple_get<I>(t) -> tuple_get<I>(t)
		//			[default]
		//				std::get<I>(t)
		//
		template<std::size_t I, typename T>
		inline SPROUT_CONSTEXPR decltype(sprout::tuples::tuple_access_traits<typename std::remove_reference<T>::type>::template tuple_get<I>(std::declval<T>()))
		get(T&& t)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::tuples::tuple_access_traits<typename std::remove_reference<T>::type>::template tuple_get<I>(std::declval<T>()))
		{
			return sprout::tuples::tuple_access_traits<typename std::remove_reference<T>::type>::template tuple_get<I>(SPROUT_FORWARD(T, t));
		}

		//
		// get
		//
		template<typename Type, typename T>
		inline SPROUT_CONSTEXPR decltype(sprout::tuples::get<(sprout::types::find_index<typename sprout::remove_cvref<T>::type, Type>::value)>(std::declval<T>()))
		get(T&& t)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::tuples::get<(sprout::types::find_index<typename sprout::remove_cvref<T>::type, Type>::value)>(std::declval<T>()))
		{
			static_assert(sprout::types::count<typename sprout::remove_cvref<T>::type, Type>::value == 1, "Requires: The type 'Type' occurs exactly once in type list.");
			return sprout::tuples::get<(sprout::types::find_index<typename sprout::remove_cvref<T>::type, Type>::value)>(SPROUT_FORWARD(T, t));
		}

		//
		// nested_get
		//
		template<std::size_t I, typename T>
		inline SPROUT_CONSTEXPR decltype(sprout::tuples::get<I>(std::declval<T>()))
		nested_get(T&& t)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::tuples::get<I>(std::declval<T>()))
		{
			return sprout::tuples::get<I>(SPROUT_FORWARD(T, t));
		}
		template<std::size_t IHead, std::size_t... ITail, typename T>
		inline SPROUT_CONSTEXPR decltype(sprout::tuples::nested_get<ITail...>(sprout::tuples::get<IHead>(std::declval<T>())))
		nested_get(T&& t)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::tuples::nested_get<ITail...>(sprout::tuples::get<IHead>(std::declval<T>())))
		{
			return sprout::tuples::nested_get<ITail...>(sprout::tuples::get<IHead>(SPROUT_FORWARD(T, t)));
		}
	}	// namespace tuples

	using sprout::tuples::get;
	using sprout::tuples::nested_get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_GET_HPP
