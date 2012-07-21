#ifndef SPROUT_TUPLE_TUPLE_GET_HPP
#define SPROUT_TUPLE_TUPLE_GET_HPP

#include <cstddef>
#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
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
		// get
		//
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

namespace sprout_tuple_detail {
	struct not_found_adl_get {};

	template<std::size_t I>
	sprout_tuple_detail::not_found_adl_get get(...);

	template<std::size_t I, typename T>
	struct has_adl_get_test {
	public:
		template<
			typename U = T,
			typename sprout::enabler_if<
				!std::is_same<decltype(get<I>(std::declval<U>())), sprout_tuple_detail::not_found_adl_get>::value
			>::type = sprout::enabler
		>
		static std::true_type test(int);
		static std::false_type test(...);
	};
	template<std::size_t I, typename T>
	struct has_adl_get
		: public decltype(sprout_tuple_detail::has_adl_get_test<I, T>::test(0))
	{};

	template<std::size_t I, typename T>
	struct has_std_get_test {
	public:
		template<
			typename U = T,
			typename = decltype(std::get<I>(std::declval<U>()))
		>
		static std::true_type test(int);
		static std::false_type test(...);
	};
	template<std::size_t I, typename T>
	struct has_std_get
		: public decltype(sprout_tuple_detail::has_std_get_test<I, T>::test(0))
	{};

	template<std::size_t I, typename T, typename Enable = void>
	struct select_adl_get;
	template<std::size_t I, typename T>
	struct select_adl_get<
		I, T,
		typename std::enable_if<sprout_tuple_detail::has_adl_get<I, T>::value>::type
	>
		: public std::true_type
	{};
	template<std::size_t I, typename T>
	struct select_adl_get<
		I, T,
		typename std::enable_if<!sprout_tuple_detail::has_adl_get<I, T>::value>::type
	>
		: public std::false_type
	{};

	template<std::size_t I, typename T, typename Enable = void>
	struct select_std_get;
	template<std::size_t I, typename T>
	struct select_std_get<
		I, T,
		typename std::enable_if<
			sprout_tuple_detail::has_std_get<I, T>::value
			&& !sprout_tuple_detail::has_adl_get<I, T>::value
		>::type
	>
		: public std::true_type
	{};
	template<std::size_t I, typename T>
	struct select_std_get<
		I, T,
		typename std::enable_if<!(
			sprout_tuple_detail::has_std_get<I, T>::value
			&& !sprout_tuple_detail::has_adl_get<I, T>::value
		)>::type
	>
		: public std::false_type
	{};

	template<std::size_t I, typename T, typename = void>
	struct noexcept_get;
	template<std::size_t I, typename T>
	struct noexcept_get<I, T, typename std::enable_if<sprout_tuple_detail::select_adl_get<I, T>::value>::type>
		: public std::integral_constant<bool, SPROUT_NOEXCEPT_EXPR_OR_DEFAULT(get<I>(std::declval<T>()), false)>
	{};
	template<std::size_t I, typename T>
	struct noexcept_get<I, T, typename std::enable_if<sprout_tuple_detail::select_std_get<I, T>::value>::type>
		: public std::integral_constant<bool, SPROUT_NOEXCEPT_EXPR_OR_DEFAULT(std::get<I>(std::declval<T>()), false)>
	{};

	template<std::size_t I, typename T, typename = void>
	struct get_result;
	template<std::size_t I, typename T>
	struct get_result<I, T, typename std::enable_if<sprout_tuple_detail::select_adl_get<I, T>::value>::type> {
	public:
		typedef decltype(get<I>(std::declval<T>())) type;
	};
	template<std::size_t I, typename T>
	struct get_result<I, T, typename std::enable_if<sprout_tuple_detail::select_std_get<I, T>::value>::type> {
	public:
		typedef decltype(std::get<I>(std::declval<T>())) type;
	};

	template<
		std::size_t I, typename T,
		typename sprout::enabler_if<sprout_tuple_detail::select_adl_get<I, T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout_tuple_detail::get_result<I, T>::type
	get_impl(T&& t)
		SPROUT_NOEXCEPT_EXPR((sprout_tuple_detail::noexcept_get<I, T>::value))
	{
		return get<I>(sprout::forward<T>(t));
	}
	template<
		std::size_t I, typename T,
		typename sprout::enabler_if<sprout_tuple_detail::select_std_get<I, T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout_tuple_detail::get_result<I, T>::type
	get_impl(T&& t)
		SPROUT_NOEXCEPT_EXPR((sprout_tuple_detail::noexcept_get<I, T>::value))
	{
		return std::get<I>(sprout::forward<T>(t));
	}
}	// namespace sprout_tuple_detail

namespace sprout {
	namespace tuples {
		//
		// get
		//
		template<std::size_t I, typename T>
		inline SPROUT_CONSTEXPR typename sprout_tuple_detail::get_result<I, T>::type
		get(T&& t)
			SPROUT_NOEXCEPT_EXPR((sprout_tuple_detail::noexcept_get<I, T>::value))
		{
			return sprout_tuple_detail::get_impl<I>(sprout::forward<T>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_GET_HPP
