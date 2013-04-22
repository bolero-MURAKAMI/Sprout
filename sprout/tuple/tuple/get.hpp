#ifndef SPROUT_TUPLE_TUPLE_GET_HPP
#define SPROUT_TUPLE_TUPLE_GET_HPP

#include <cstddef>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/tuple_size.hpp>
#include <sprout/tuple/tuple/tuple_element.hpp>
#include <sprout/tuple/tuple/tuple_access_traits.hpp>
#include <sprout/adl/not_found.hpp>

//#include <tuple>
//#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t I, typename Head, typename... Tail>
			inline SPROUT_CONSTEXPR typename std::add_lvalue_reference<Head>::type
			get_helper(sprout::tuples::detail::tuple_impl<I, Head, Tail...>& t) SPROUT_NOEXCEPT {
				return sprout::tuples::detail::tuple_impl<I, Head, Tail...>::head(t);
			}
			template<std::size_t I, typename Head, typename... Tail>
			inline SPROUT_CONSTEXPR typename std::add_lvalue_reference<typename std::add_const<Head>::type>::type
			get_helper(sprout::tuples::detail::tuple_impl<I, Head, Tail...> const& t) SPROUT_NOEXCEPT {
				return sprout::tuples::detail::tuple_impl<I, Head, Tail...>::head(t);
			}
		}	// namespace detail
		//
		// tuple_get
		//
		template<std::size_t I, typename... Types>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type&
		tuple_get(sprout::tuples::tuple<Types...>& t) SPROUT_NOEXCEPT {
			return sprout::tuples::detail::get_helper<I>(t);
		}
		template<std::size_t I, typename... Types>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type&&
		tuple_get(sprout::tuples::tuple<Types...>&& t) SPROUT_NOEXCEPT {
			return sprout::forward<typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type&&>(
				sprout::tuples::tuple_get<I>(t)
				);
		}
		template<std::size_t I, typename... Types>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type const&
		tuple_get(sprout::tuples::tuple<Types...> const& t) SPROUT_NOEXCEPT {
			return sprout::tuples::detail::get_helper<I>(t);
		}
	}	// namespace tuples

	using sprout::tuples::tuple_get;
}	// namespace sprout

namespace sprout_adl {
	template<std::size_t I>
	sprout::not_found_via_adl tuple_get(...);
}	// namespace sprout_adl

namespace sprout_tuple_detail {
	using sprout_adl::tuple_get;

	template<std::size_t I, typename T>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, T>::type&
	tuple_get(T& t)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::tuple_access_traits<T>::template tuple_get<I>(std::declval<T>())))
	{
		return sprout::tuples::tuple_access_traits<T>::template tuple_get<I>(t);
	}
	template<std::size_t I, typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<T>::value && !std::is_volatile<T>::value && !std::is_reference<T>::value,
		typename sprout::tuples::tuple_element<I, typename std::remove_reference<T>::type>::type&&
	>::type
	tuple_get(T&& t)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::tuple_access_traits<typename std::remove_reference<T>::type>::template tuple_get<I>(std::declval<T>())))
	{
		return sprout::tuples::tuple_access_traits<T>::template tuple_get<I>(t);
	}
	template<std::size_t I, typename T>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, T>::type const&
	tuple_get(T const& t)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::tuple_access_traits<T const>::template tuple_get<I>(std::declval<T>())))
	{
		return sprout::tuples::tuple_access_traits<T const>::template tuple_get<I>(t);
	}

	template<std::size_t I, typename T>
	inline SPROUT_CONSTEXPR decltype(tuple_get<I>(std::declval<T>()))
	call_tuple_get(T&& t)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(tuple_get<I>(std::declval<T>())))
	{
		return tuple_get<I>(sprout::forward<T>(t));
	}
}	// namespace sprout_tuple_detail

namespace sprout {
	namespace tuples {
		//
		// get
		//
		template<std::size_t I, typename T>
		inline SPROUT_CONSTEXPR decltype(sprout_tuple_detail::call_tuple_get<I>(std::declval<T>()))
		get(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout_tuple_detail::call_tuple_get<I>(std::declval<T>())))
		{
			return sprout_tuple_detail::call_tuple_get<I>(sprout::forward<T>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_GET_HPP
