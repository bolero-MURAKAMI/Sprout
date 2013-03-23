#ifndef SPROUT_TYPE_TRAITS_ARITHMETIC_PROMOTE_HPP
#define SPROUT_TYPE_TRAITS_ARITHMETIC_PROMOTE_HPP

#include <type_traits>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace detail {
		template <typename T>
		struct arithmetic_promote1
			: public sprout::identity<T>
		{
			static_assert(
				std::is_arithmetic<T>::value,
				"arithmetic_promote requires arithmetic types."
				);
		};

		template <typename T, typename U>
		struct arithmetic_promote2
			: public std::decay<decltype(std::declval<T>() + std::declval<U>())>
		{
			static_assert(
				std::is_arithmetic<T>::value && std::is_arithmetic<U>::value,
				"arithmetic_promote requires arithmetic types."
				);
		};

		template<typename... Types>
		struct arithmetic_promote_impl;
		template<typename T, typename U, typename... Tail>
		struct arithmetic_promote_impl<T, U, Tail...>
			: public sprout::detail::arithmetic_promote_impl<
				typename sprout::detail::arithmetic_promote2<T, U>::type,
				Tail...
			>
		{};
		template<typename T>
		struct arithmetic_promote_impl<T>
			: public sprout::detail::arithmetic_promote1<T>
		{};
	}	// namespace detail

	//
	// arithmetic_promote
	//
	template<typename... Types>
	struct arithmetic_promote
		: public sprout::detail::arithmetic_promote_impl<
			typename std::remove_cv<Types>::type...
		>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename... Types>
	using arithmetic_promote_ = typename sprout::arithmetic_promote<Types...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_ARITHMETIC_PROMOTE_HPP
