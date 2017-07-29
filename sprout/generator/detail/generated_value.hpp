/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_DETAIL_GENERATED_VALUE_HPP
#define SPROUT_GENERATOR_DETAIL_GENERATED_VALUE_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/iterator/const_reference_cast.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl get_generated_value(...);
}	// namespace sprout_adl

namespace sprout {
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
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_generated_value_test<T>::test(0))>::type>
		struct has_mem_generated_value
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_generated_value
			: public sprout::identity<decltype(sprout::detail::has_mem_generated_value_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_generated_value
			: public sprout::bool_constant<
				sprout::detail::has_mem_generated_value<T const>::value
			>
		{};

		template<typename Gen, typename = void>
		struct get_generated_value_impl;

		template<typename Gen>
		struct get_generated_value_impl<
			Gen,
			typename std::enable_if<
				std::is_lvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& sprout::detail::is_substitutable_const_generated_value<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().generated_value())
			get_generated_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().generated_value())
			{
				typedef decltype(std::declval<Gen>().generated_value()) type;
				return sprout::const_reference_cast<type>(sprout::as_const(gen).generated_value());
			}
		};
		template<typename Gen>
		struct get_generated_value_impl<
			Gen,
			typename std::enable_if<
				std::is_lvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::is_substitutable_const_generated_value<Gen>::value
					&& sprout::detail::has_mem_generated_value<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().generated_value())
			get_generated_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().generated_value())
			{
				return gen.generated_value();
			}
		};
		template<typename Gen>
		struct get_generated_value_impl<
			Gen,
			typename std::enable_if<
				std::is_lvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::is_substitutable_const_generated_value<Gen>::value
					&& !sprout::detail::has_mem_generated_value<Gen>::value
					&& sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(*std::declval<Gen>())
			get_generated_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(*std::declval<Gen>())
			{
				return *gen;
			}
		};
		template<typename Gen>
		struct get_generated_value_impl<
			Gen,
			typename std::enable_if<
				std::is_lvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::is_substitutable_const_generated_value<Gen>::value
					&& !sprout::detail::has_mem_generated_value<Gen>::value
					&& !sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::tuples::get<0>(std::declval<Gen>()))
			get_generated_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::tuples::get<0>(std::declval<Gen>()))
			{
				return sprout::tuples::get<0>(gen);
			}
		};

		template<typename Gen>
		struct get_generated_value_impl<
			Gen,
			typename std::enable_if<
				std::is_rvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& sprout::detail::is_substitutable_const_generated_value<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().generated_value())
			get_generated_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().generated_value())
			{
				typedef decltype(std::declval<Gen>().generated_value()) type;
				return sprout::const_reference_cast<type>(sprout::as_const(sprout::move(gen)).generated_value());
			}
		};
		template<typename Gen>
		struct get_generated_value_impl<
			Gen,
			typename std::enable_if<
				std::is_rvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::is_substitutable_const_generated_value<Gen>::value
					&& sprout::detail::has_mem_generated_value<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().generated_value())
			get_generated_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().generated_value())
			{
				return sprout::move(gen).generated_value();
			}
		};
		template<typename Gen>
		struct get_generated_value_impl<
			Gen,
			typename std::enable_if<
				std::is_rvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::is_substitutable_const_generated_value<Gen>::value
					&& !sprout::detail::has_mem_generated_value<Gen>::value
					&& sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(*std::declval<Gen>())
			get_generated_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(*std::declval<Gen>())
			{
				return *sprout::move(gen);
			}
		};
		template<typename Gen>
		struct get_generated_value_impl<
			Gen,
			typename std::enable_if<
				std::is_rvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::is_substitutable_const_generated_value<Gen>::value
					&& !sprout::detail::has_mem_generated_value<Gen>::value
					&& !sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::tuples::get<0>(std::declval<Gen>()))
			get_generated_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::tuples::get<0>(std::declval<Gen>()))
			{
				return sprout::tuples::get<0>(sprout::move(gen));
			}
		};

		template<typename Gen>
		struct get_generated_value_impl<
			Gen,
			typename std::enable_if<
				std::is_reference<Gen>::value && std::is_const<typename std::remove_reference<Gen>::type>::value
					&& sprout::detail::has_mem_generated_value<Gen const>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().generated_value())
			get_generated_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().generated_value())
			{
				return gen.generated_value();
			}
		};
		template<typename Gen>
		struct get_generated_value_impl<
			Gen,
			typename std::enable_if<
				std::is_reference<Gen>::value && std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_generated_value<Gen const>::value
					&& sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(*std::declval<Gen>())
			get_generated_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(*std::declval<Gen>())
			{
				return *gen;
			}
		};
		template<typename Gen>
		struct get_generated_value_impl<
			Gen,
			typename std::enable_if<
				std::is_reference<Gen>::value && std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_generated_value<Gen const>::value
					&& !sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::tuples::get<0>(std::declval<Gen>()))
			get_generated_value(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::tuples::get<0>(std::declval<Gen>()))
			{
				return sprout::tuples::get<0>(gen);
			}
		};
	}	// namespace detail
}	// namespace sprout

namespace sprout_generator_detail {
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::detail::get_generated_value_impl<Gen&>::get_generated_value(std::declval<Gen&>()))
	get_generated_value(Gen& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::detail::get_generated_value_impl<Gen&>::get_generated_value(std::declval<Gen&>()))
	{
		return sprout::detail::get_generated_value_impl<Gen&>::get_generated_value(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(sprout::detail::get_generated_value_impl<Gen&&>::get_generated_value(std::declval<Gen&&>()))
	>::type
	get_generated_value(Gen&& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::detail::get_generated_value_impl<Gen&&>::get_generated_value(std::declval<Gen&&>()))
	{
		return sprout::detail::get_generated_value_impl<Gen&&>::get_generated_value(sprout::move(gen));
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::detail::get_generated_value_impl<Gen const&>::get_generated_value(std::declval<Gen const&>()))
	get_generated_value(Gen const& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::detail::get_generated_value_impl<Gen const&>::get_generated_value(std::declval<Gen const&>()))
	{
		return sprout::detail::get_generated_value_impl<Gen const&>::get_generated_value(gen);
	}
}	// namespace sprout_generator_detail

#endif	// #ifndef SPROUT_GENERATOR_DETAIL_GENERATED_VALUE_HPP
