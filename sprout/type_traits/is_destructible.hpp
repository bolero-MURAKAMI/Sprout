/*=============================================================================
	Copyright (c) 2011-2015 Bolero MURAKAMI
	https://github.com/bolero-MURAKAMI/Sprout

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP
#define SPROUT_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	//
	// is_destructible
	//
	namespace detail {
		struct is_destructible_helper_1 {
		public:
			template<typename U>
			struct w {
				U u;
			};
			template<
				typename T,
				typename = decltype(std::declval<w<T>&>().~w<T>())
			>
			static sprout::true_type test(int);
			template<typename>
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER)
		template<typename T, typename Base_ = sprout::identity<decltype(sprout::detail::is_destructible_helper_1::test<T>(0))>::type>
		struct is_destructible_impl_1
			: public Base_
		{};
#else
		template<typename T>
		struct is_destructible_impl_1
			: public sprout::identity<decltype(sprout::detail::is_destructible_helper_1::test<T>(0))>::type
		{};
#endif

		struct is_destructible_helper_2 {
		public:
			template<
				typename T,
				typename = decltype(std::declval<T&>().~T())
			>
			static sprout::true_type test(int);
			template<typename>
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER)
		template<typename T, typename Base_ = sprout::identity<decltype(sprout::detail::is_destructible_helper_2::test<T>(0))>::type>
		struct is_destructible_impl_2
			: public Base_
		{};
#else
		template<typename T>
		struct is_destructible_impl_2
			: public sprout::identity<decltype(sprout::detail::is_destructible_helper_2::test<T>(0))>::type
		{};
#endif

		struct is_destructible_helper {
		public:
			template<
				typename T,
				typename = decltype(std::declval<T&>().~T())
			>
			static sprout::true_type test(int);
			template<typename>
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER)
		template<typename T, typename Base_ = sprout::identity<decltype(sprout::detail::is_destructible_helper::test<T>(0))>::type>
		struct is_destructible_impl_0
			: public Base_
		{};
#else
		template<typename T>
		struct is_destructible_impl_0
			: public sprout::identity<decltype(sprout::detail::is_destructible_helper::test<T>(0))>::type
		{};
#endif

		template<
			typename T,
			bool = std::is_void<T>::value || (std::is_array<T>::value && !std::extent<T>::value) || std::is_function<T>::value,
			bool = std::is_reference<T>::value || std::is_scalar<T>::value
		>
		struct is_destructible_impl;
		template<typename T>
		struct is_destructible_impl<T, false, false>
			: public sprout::detail::is_destructible_impl_0<typename std::remove_all_extents<T>::type>
		{};
		template<typename T>
		struct is_destructible_impl<T, true, false>
			: public sprout::false_type
		{};
		template<typename T>
		struct is_destructible_impl<T, false, true>
			: public sprout::true_type
		{};
	}	// namespace detail
	template<typename T>
	struct is_destructible
		: public sprout::detail::is_destructible_impl<T>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP
