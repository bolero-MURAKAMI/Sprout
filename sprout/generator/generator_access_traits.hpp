/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_GENERATOR_ACCESS_TRAITS_HPP
#define SPROUT_GENERATOR_GENERATOR_ACCESS_TRAITS_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>

namespace sprout {
	namespace generators {
		namespace detail {
			template<typename T>
			struct has_mem_generated_value_test {
			public:
				template<
					typename U = T,
					typename = decltype(std::declval<U>().generated_value())
				>
				static std::true_type test(int);
				static std::false_type test(...);
			};
#if defined(_MSC_VER)
			template<typename T, typename Base_ = decltype(sprout::generators::detail::has_mem_generated_value_test<T>::test(0))>
			struct has_mem_generated_value
				: public Base_
			{};
#else
			template<typename T>
			struct has_mem_generated_value
				: public decltype(sprout::generators::detail::has_mem_generated_value_test<T>::test(0))
			{};
#endif

			template<typename Gen, typename = void>
			struct generator_access_traits_generated_value_impl;
			template<typename Gen>
			struct generator_access_traits_generated_value_impl<
				Gen,
				typename std::enable_if<sprout::generators::detail::has_mem_generated_value<Gen>::value>::type
			> {
			public:
				static SPROUT_CONSTEXPR decltype(std::declval<Gen&>().generated_value())
				get_generated_value(Gen& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<Gen&>().generated_value()))
				{
					return t.generated_value();
				}
				static SPROUT_CONSTEXPR decltype(std::declval<Gen&&>().generated_value())
				get_generated_value(Gen&& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<Gen&&>().generated_value()))
				{
					return t.generated_value();
				}
				static SPROUT_CONSTEXPR decltype(std::declval<Gen const&>().generated_value())
				get_generated_value(Gen const& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<Gen const&>().generated_value()))
				{
					return t.generated_value();
				}
			};
			template<typename Gen>
			struct generator_access_traits_generated_value_impl<
				Gen,
				typename std::enable_if<!sprout::generators::detail::has_mem_generated_value<Gen>::value>::type
			> {
			public:
				static SPROUT_CONSTEXPR decltype(sprout::tuples::get<0>(std::declval<Gen&>()))
				get_generated_value(Gen& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::get<0>(std::declval<Gen&>())))
				{
					return sprout::tuples::get<0>(t);
				}
				static SPROUT_CONSTEXPR decltype(sprout::tuples::get<0>(std::declval<Gen&&>()))
				get_generated_value(Gen&& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::get<0>(std::declval<Gen&>())))
				{
					return sprout::tuples::get<0>(t);
				}
				static SPROUT_CONSTEXPR decltype(sprout::tuples::get<0>(std::declval<Gen const&>()))
				get_generated_value(Gen const& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::get<0>(std::declval<Gen const&>())))
				{
					return sprout::tuples::get<0>(t);
				}
			};

			template<typename T>
			struct has_mem_next_generator_test {
			public:
				template<
					typename U = T,
					typename = decltype(std::declval<U>().next_generator())
				>
				static std::true_type test(int);
				static std::false_type test(...);
			};
#if defined(_MSC_VER)
			template<typename T, typename Base_ = decltype(sprout::generators::detail::has_mem_next_generator_test<T>::test(0))>
			struct has_mem_next_generator
				: public Base_
			{};
#else
			template<typename T>
			struct has_mem_next_generator
				: public decltype(sprout::generators::detail::has_mem_next_generator_test<T>::test(0))
			{};
#endif

			template<typename Gen, typename = void>
			struct generator_access_traits_next_generator_impl;
			template<typename Gen>
			struct generator_access_traits_next_generator_impl<
				Gen,
				typename std::enable_if<sprout::generators::detail::has_mem_next_generator<Gen>::value>::type
			> {
			public:
				static SPROUT_CONSTEXPR decltype(std::declval<Gen&>().next_generator())
				get_next_generator(Gen& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<Gen&>().next_generator()))
				{
					return t.next_generator();
				}
				static SPROUT_CONSTEXPR decltype(std::declval<Gen&&>().next_generator())
				get_next_generator(Gen&& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<Gen&&>().next_generator()))
				{
					return t.next_generator();
				}
				static SPROUT_CONSTEXPR decltype(std::declval<Gen const&>().next_generator())
				get_next_generator(Gen const& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<Gen const&>().next_generator()))
				{
					return t.next_generator();
				}
			};
			template<typename Gen>
			struct generator_access_traits_next_generator_impl<
				Gen,
				typename std::enable_if<!sprout::generators::detail::has_mem_next_generator<Gen>::value>::type
			> {
			public:
				static SPROUT_CONSTEXPR decltype(sprout::tuples::get<1>(std::declval<Gen&>()))
				get_next_generator(Gen& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::get<1>(std::declval<Gen&>())))
				{
					return sprout::tuples::get<1>(t);
				}
				static SPROUT_CONSTEXPR decltype(sprout::tuples::get<1>(std::declval<Gen&&>()))
				get_next_generator(Gen&& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::get<1>(std::declval<Gen&>())))
				{
					return sprout::tuples::get<1>(t);
				}
				static SPROUT_CONSTEXPR decltype(sprout::tuples::get<1>(std::declval<Gen const&>()))
				get_next_generator(Gen const& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::get<1>(std::declval<Gen const&>())))
				{
					return sprout::tuples::get<1>(t);
				}
			};
		}	// namespace detail

		//
		// generator_access_traits
		//
		template<typename Gen>
		struct generator_access_traits
			: public sprout::generators::detail::generator_access_traits_generated_value_impl<Gen>
			, public sprout::generators::detail::generator_access_traits_next_generator_impl<Gen>
		{};
		template<typename Gen>
		struct generator_access_traits<Gen const> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen>::get_generated_value(std::declval<Gen const&>()))
			get_generated_value(Gen const& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::generators::generator_access_traits<Gen>::get_generated_value(std::declval<Gen const&>())))
			{
				return sprout::generators::generator_access_traits<Gen>::get_generated_value(t);
			}
			static SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen>::get_next_generator(std::declval<Gen const&>()))
			get_next_generator(Gen const& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::generators::generator_access_traits<Gen>::get_next_generator(std::declval<Gen const&>())))
			{
				return sprout::generators::generator_access_traits<Gen>::get_next_generator(t);
			}
		};
	}	// namespace generators

	using sprout::generators::generator_access_traits;
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_GENERATOR_ACCESS_TRAITS_HPP
