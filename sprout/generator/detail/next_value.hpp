/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_DETAIL_NEXT_VALUE_HPP
#define SPROUT_GENERATOR_DETAIL_NEXT_VALUE_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/iterator/const_reference_cast.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/generator/access_functions_fwd.hpp>
#include <sprout/generator/next_generator.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl generate_next_value(...);
}	// namespace sprout_adl

namespace sprout {
	namespace detail {
		template<typename T>
		struct has_mem_next_value_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().next_value())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_next_value_test<T>::test(0))>::type>
		struct has_mem_next_value
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_next_value
			: public sprout::identity<decltype(sprout::detail::has_mem_next_value_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct has_function_call_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>()())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_function_call_test<T>::test(0))>::type>
		struct has_function_call
			: public Base_
		{};
#else
		template<typename T>
		struct has_function_call
			: public sprout::identity<decltype(sprout::detail::has_function_call_test<T>::test(0))>::type
		{};
#endif

		template<typename Gen, typename = void>
		struct generate_next_value_impl;

		template<typename Gen>
		struct generate_next_value_impl<
			Gen,
			typename std::enable_if<
				std::is_lvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& sprout::detail::has_mem_next_value<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().next_value())
			generate_next_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().next_value())
			{
				return gen.next_value();
			}
		};
		template<typename Gen>
		struct generate_next_value_impl<
			Gen,
			typename std::enable_if<
				std::is_lvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_next_value<Gen>::value
					&& sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::next(std::declval<Gen>()))
			generate_next_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::next(std::declval<Gen>()))
			{
				return sprout::next(gen);
			}
		};
		template<typename Gen>
		struct generate_next_value_impl<
			Gen,
			typename std::enable_if<
				std::is_lvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_next_value<Gen>::value
					&& !sprout::is_input_iterator<Gen>::value
					&& sprout::detail::has_function_call<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>()())
			generate_next_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>()())
			{
				return gen();
			}
		};
		template<typename Gen>
		struct generate_next_value_impl<
			Gen,
			typename std::enable_if<
				std::is_lvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_next_value<Gen>::value
					&& !sprout::is_input_iterator<Gen>::value
					&& !sprout::detail::has_function_call<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::generators::next_value(sprout::generators::next_generator(std::declval<Gen>())))
			generate_next_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::next_value(sprout::generators::next_generator(std::declval<Gen>())))
			{
				return sprout::generators::next_value(sprout::generators::next_generator(gen));
			}
		};

		template<typename Gen>
		struct generate_next_value_impl<
			Gen,
			typename std::enable_if<
				std::is_rvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& sprout::detail::has_mem_next_value<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().next_value())
			generate_next_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().next_value())
			{
				return sprout::move(gen).next_value();
			}
		};
		template<typename Gen>
		struct generate_next_value_impl<
			Gen,
			typename std::enable_if<
				std::is_rvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_next_value<Gen>::value
					&& sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::next(std::declval<Gen>()))
			generate_next_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::next(std::declval<Gen>()))
			{
				return sprout::next(sprout::move(gen));
			}
		};
		template<typename Gen>
		struct generate_next_value_impl<
			Gen,
			typename std::enable_if<
				std::is_rvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_next_value<Gen>::value
					&& !sprout::is_input_iterator<Gen>::value
					&& sprout::detail::has_function_call<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>()())
			generate_next_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>()())
			{
				return sprout::move(gen)();
			}
		};
		template<typename Gen>
		struct generate_next_value_impl<
			Gen,
			typename std::enable_if<
				std::is_rvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_next_value<Gen>::value
					&& !sprout::is_input_iterator<Gen>::value
					&& !sprout::detail::has_function_call<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::generators::next_value(sprout::generators::next_generator(std::declval<Gen>())))
			generate_next_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::next_value(sprout::generators::next_generator(std::declval<Gen>())))
			{
				return sprout::generators::next_value(sprout::generators::next_generator(sprout::move(gen)));
			}
		};

		template<typename Gen>
		struct generate_next_value_impl<
			Gen,
			typename std::enable_if<
				std::is_reference<Gen>::value && std::is_const<typename std::remove_reference<Gen>::type>::value
					&& sprout::detail::has_mem_next_value<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().next_value())
			generate_next_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().next_value())
			{
				return gen.next_value();
			}
		};
		template<typename Gen>
		struct generate_next_value_impl<
			Gen,
			typename std::enable_if<
				std::is_reference<Gen>::value && std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_next_value<Gen>::value
					&& sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::next(std::declval<Gen>()))
			generate_next_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::next(std::declval<Gen>()))
			{
				return sprout::next(gen);
			}
		};
		template<typename Gen>
		struct generate_next_value_impl<
			Gen,
			typename std::enable_if<
				std::is_reference<Gen>::value && std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_next_value<Gen>::value
					&& !sprout::is_input_iterator<Gen>::value
					&& sprout::detail::has_function_call<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>()())
			generate_next_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>()())
			{
				return gen();
			}
		};
		template<typename Gen>
		struct generate_next_value_impl<
			Gen,
			typename std::enable_if<
				std::is_reference<Gen>::value && std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_next_value<Gen>::value
					&& !sprout::is_input_iterator<Gen>::value
					&& !sprout::detail::has_function_call<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::generators::next_value(sprout::generators::next_generator(std::declval<Gen>())))
			generate_next_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::next_value(sprout::generators::next_generator(std::declval<Gen>())))
			{
				return sprout::generators::next_value(sprout::generators::next_generator(gen));
			}
		};
	}	// namespace detail
}	// namespace sprout

namespace sprout_generator_detail {
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::detail::generate_next_value_impl<Gen&>::generate_next_value(std::declval<Gen&>()))
	generate_next_value(Gen& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::detail::generate_next_value_impl<Gen&>::generate_next_value(std::declval<Gen&>()))
	{
		return sprout::detail::generate_next_value_impl<Gen&>::generate_next_value(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(sprout::detail::generate_next_value_impl<Gen&&>::generate_next_value(std::declval<Gen&&>()))
	>::type
	generate_next_value(Gen&& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::detail::generate_next_value_impl<Gen&&>::generate_next_value(std::declval<Gen&&>()))
	{
		return sprout::detail::generate_next_value_impl<Gen&&>::generate_next_value(sprout::move(gen));
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::detail::generate_next_value_impl<Gen const&>::generate_next_value(std::declval<Gen const&>()))
	generate_next_value(Gen const& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::detail::generate_next_value_impl<Gen const&>::generate_next_value(std::declval<Gen const&>()))
	{
		return sprout::detail::generate_next_value_impl<Gen const&>::generate_next_value(gen);
	}
}	// namespace sprout_generator_detail

#endif	// #ifndef SPROUT_GENERATOR_DETAIL_NEXT_VALUE_HPP
