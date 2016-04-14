/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_GENERATOR_ACCESS_TRAITS_HPP
#define SPROUT_GENERATOR_GENERATOR_ACCESS_TRAITS_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl get_generated_value(...);
	sprout::not_found_via_adl get_next_generator(...);
}	// namespace sprout_adl

namespace sprout {
	namespace generators {
		namespace detail {
			template<typename T>
			struct has_mem_generated_value_test {
			public:
				template<
					typename U = T,
					typename = typename sprout::identity<decltype(std::declval<U>().generated_value())>::type
				>
				static sprout::true_type test(int);
				static sprout::false_type test(...);
			};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
			template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::generators::detail::has_mem_generated_value_test<T>::test(0))>::type>
			struct has_mem_generated_value
				: public Base_
			{};
#else
			template<typename T>
			struct has_mem_generated_value
				: public sprout::identity<decltype(sprout::generators::detail::has_mem_generated_value_test<T>::test(0))>::type
			{};
#endif

			template<typename Gen, typename = void>
			struct get_generated_value_helper;
			template<typename Gen>
			struct get_generated_value_helper<
				Gen,
				typename std::enable_if<sprout::generators::detail::has_mem_generated_value<Gen>::value>::type
			> {
			public:
				static SPROUT_CONSTEXPR decltype(std::declval<Gen>().generated_value())
				call(Gen&& t)
				SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().generated_value())
				{
					return SPROUT_FORWARD(Gen, t).generated_value();
				}
			};
			template<typename Gen>
			struct get_generated_value_helper<
				Gen,
				typename std::enable_if<!sprout::generators::detail::has_mem_generated_value<Gen>::value>::type
			> {
			public:
				static SPROUT_CONSTEXPR decltype(sprout::tuples::get<0>(std::declval<Gen>()))
				call(Gen&& t)
				SPROUT_NOEXCEPT_IF_EXPR(sprout::tuples::get<0>(std::declval<Gen>()))
				{
					return sprout::tuples::get<0>(SPROUT_FORWARD(Gen, t));
				}
			};
			template<typename Gen>
			inline SPROUT_CONSTEXPR decltype(sprout::generators::detail::get_generated_value_helper<Gen>::call(std::declval<Gen>()))
			get_generated_value_impl(Gen&& t) {
				return sprout::generators::detail::get_generated_value_helper<Gen>::call(SPROUT_FORWARD(Gen, t));
			}

			template<typename T>
			struct has_mem_next_generator_test {
			public:
				template<
					typename U = T,
					typename = typename sprout::identity<decltype(std::declval<U>().next_generator())>::type
				>
				static sprout::true_type test(int);
				static sprout::false_type test(...);
			};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
			template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::generators::detail::has_mem_next_generator_test<T>::test(0))>::type>
			struct has_mem_next_generator
				: public Base_
			{};
#else
			template<typename T>
			struct has_mem_next_generator
				: public sprout::identity<decltype(sprout::generators::detail::has_mem_next_generator_test<T>::test(0))>::type
			{};
#endif

			template<typename Gen, typename = void>
			struct get_next_generator_helper;
			template<typename Gen>
			struct get_next_generator_helper<
				Gen,
				typename std::enable_if<sprout::generators::detail::has_mem_next_generator<Gen>::value>::type
			> {
			public:
				static SPROUT_CONSTEXPR decltype(std::declval<Gen>().next_generator())
				call(Gen&& t)
				SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().next_generator())
				{
					return t.next_generator();
				}
			};
			template<typename Gen>
			struct get_next_generator_helper<
				Gen,
				typename std::enable_if<!sprout::generators::detail::has_mem_next_generator<Gen>::value>::type
			> {
			public:
				static SPROUT_CONSTEXPR decltype(sprout::tuples::get<1>(std::declval<Gen>()))
				call(Gen&& t)
				SPROUT_NOEXCEPT_IF_EXPR(sprout::tuples::get<1>(std::declval<Gen>()))
				{
					return sprout::tuples::get<1>(SPROUT_FORWARD(Gen, t));
				}
			};
			template<typename Gen>
			inline SPROUT_CONSTEXPR decltype(sprout::generators::detail::get_next_generator_helper<Gen>::call(std::declval<Gen>()))
			get_next_generator_impl(Gen&& t) {
				return sprout::generators::detail::get_next_generator_helper<Gen>::call(SPROUT_FORWARD(Gen, t));
			}
		}	// namespace detail
	}	// namespace generators
}	// namespace sprout

namespace sprout_generator_detail {
	using sprout_adl::get_generated_value;
	using sprout_adl::get_next_generator;

	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::generators::detail::get_generated_value_impl(std::declval<Gen&>()))
	get_generated_value(Gen& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::detail::get_generated_value_impl(std::declval<Gen&>()))
	{
		return sprout::generators::detail::get_generated_value_impl(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(sprout::generators::detail::get_generated_value_impl(std::declval<Gen&&>()))
	>::type
	get_generated_value(Gen&& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::detail::get_generated_value_impl(std::declval<Gen&&>()))
	{
		return sprout::generators::detail::get_generated_value_impl(sprout::move(gen));
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::generators::detail::get_generated_value_impl(std::declval<Gen const&>()))
	get_generated_value(Gen const& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::detail::get_generated_value_impl(std::declval<Gen const&>()))
	{
		return sprout::generators::detail::get_generated_value_impl(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(get_generated_value(std::declval<Gen>()))
	call_get_generated_value(Gen&& gen)
	SPROUT_NOEXCEPT_IF_EXPR(get_generated_value(std::declval<Gen>()))
	{
		return get_generated_value(SPROUT_FORWARD(Gen, gen));
	}

	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::generators::detail::get_next_generator_impl(std::declval<Gen&>()))
	get_next_generator(Gen& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::detail::get_next_generator_impl(std::declval<Gen&>()))
	{
		return sprout::generators::detail::get_next_generator_impl(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(sprout::generators::detail::get_next_generator_impl(std::declval<Gen&&>()))
	>::type
	get_next_generator(Gen&& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::detail::get_next_generator_impl(std::declval<Gen&&>()))
	{
		return sprout::generators::detail::get_next_generator_impl(sprout::move(gen));
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::generators::detail::get_next_generator_impl(std::declval<Gen const&>()))
	get_next_generator(Gen const& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::detail::get_next_generator_impl(std::declval<Gen const&>()))
	{
		return sprout::generators::detail::get_next_generator_impl(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(get_next_generator(std::declval<Gen>()))
	call_get_next_generator(Gen&& gen)
	SPROUT_NOEXCEPT_IF_EXPR(get_next_generator(std::declval<Gen>()))
	{
		return get_next_generator(SPROUT_FORWARD(Gen, gen));
	}
}	// namespace sprout_generator_detail

namespace sprout {
	namespace generators {
		//
		// generator_access_traits
		//
		template<typename Gen>
		struct generator_access_traits {
		public:
			// get_generated_value
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_generated_value(std::declval<Gen&>()))
			get_generated_value(Gen& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_generated_value(std::declval<Gen&>()))
			{
				return sprout_generator_detail::call_get_generated_value(t);
			}
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_generated_value(std::declval<Gen&&>()))
			get_generated_value(Gen&& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_generated_value(std::declval<Gen&&>()))
			{
				return sprout_generator_detail::call_get_generated_value(sprout::move(t));
			}
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_generated_value(std::declval<Gen const&>()))
			get_generated_value(Gen const& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_generated_value(std::declval<Gen const&>()))
			{
				return sprout_generator_detail::call_get_generated_value(t);
			}
			// get_next_generator
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_next_generator(std::declval<Gen&>()))
			get_next_generator(Gen& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_next_generator(std::declval<Gen&>()))
			{
				return sprout_generator_detail::call_get_next_generator(t);
			}
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_next_generator(std::declval<Gen&&>()))
			get_next_generator(Gen&& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_next_generator(std::declval<Gen&&>()))
			{
				return sprout_generator_detail::call_get_next_generator(sprout::move(t));
			}
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_next_generator(std::declval<Gen const&>()))
			get_next_generator(Gen const& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_next_generator(std::declval<Gen const&>()))
			{
				return sprout_generator_detail::call_get_next_generator(t);
			}
		};
		template<typename Gen>
		struct generator_access_traits<Gen const> {
		public:
			// get_generated_value
			static SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen>::get_generated_value(std::declval<Gen const&>()))
			get_generated_value(Gen const& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_access_traits<Gen>::get_generated_value(std::declval<Gen const&>()))
			{
				return sprout::generators::generator_access_traits<Gen>::get_generated_value(t);
			}
			// get_next_generator
			static SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen>::get_next_generator(std::declval<Gen const&>()))
			get_next_generator(Gen const& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_access_traits<Gen>::get_next_generator(std::declval<Gen const&>()))
			{
				return sprout::generators::generator_access_traits<Gen>::get_next_generator(t);
			}
		};
	}	// namespace generators

	using sprout::generators::generator_access_traits;
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_GENERATOR_ACCESS_TRAITS_HPP
