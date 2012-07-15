#ifndef SPROUT_TUPLE_TUPLE_GET_HPP
#define SPROUT_TUPLE_TUPLE_GET_HPP

#include <cstddef>
#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/tuple/tuple/tuple.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_size
		//
		template<typename T>
		struct tuple_size
			: public std::tuple_size<T>
		{};
		template<typename T>
		struct tuple_size<T const>
			: public sprout::tuples::tuple_size<T>
		{};
		template<typename T>
		struct tuple_size<T volatile>
			: public sprout::tuples::tuple_size<T>
		{};
		template<typename T>
		struct tuple_size<T const volatile>
			: public sprout::tuples::tuple_size<T>
		{};

		//
		// tuple_element
		//
		template<std::size_t I, typename T>
		struct tuple_element
			: public std::tuple_element<I, T>
		{};
		template<std::size_t I, typename T>
		struct tuple_element<I, T const>
			: public sprout::tuples::tuple_element<I, T>
		{};
		template<std::size_t I, typename T>
		struct tuple_element<I, T volatile>
			: public sprout::tuples::tuple_element<I, T>
		{};
		template<std::size_t I, typename T>
		struct tuple_element<I, T const volatile>
			: public sprout::tuples::tuple_element<I, T>
		{};

		//
		// get
		//
		template<std::size_t I, typename T>
		inline SPROUT_CONSTEXPR auto
		get(T&& t) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::get<I>(sprout::forward<T>(t))))
			-> decltype(std::get<I>(sprout::forward<T>(t)))
		{
			return std::get<I>(sprout::forward<T>(t));
		}
		//
		// get
		//
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
		template<std::size_t I, typename... Types>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type&
		get(sprout::tuples::tuple<Types...>& t) SPROUT_NOEXCEPT {
			return sprout::tuples::detail::get_helper<I>(t);
		}
		template<std::size_t I, typename... Types>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type&&
		get(sprout::tuples::tuple<Types...>&& t) SPROUT_NOEXCEPT {
			return sprout::forward<typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type&&>(
				sprout::tuples::get<I>(t)
				);
		}
		template<std::size_t I, typename... Types>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type const&
		get(sprout::tuples::tuple<Types...> const& t) SPROUT_NOEXCEPT {
			return sprout::tuples::detail::get_helper<I>(t);
		}
	}	// namespace tuples

	using sprout::tuples::tuple_size;
	using sprout::tuples::tuple_element;
	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_GET_HPP
