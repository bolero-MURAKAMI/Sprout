/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_DETAIL_NEXT_GENERATOR_HPP
#define SPROUT_GENERATOR_DETAIL_NEXT_GENERATOR_HPP

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
	sprout::not_found_via_adl get_next_generator(...);
}	// namespace sprout_adl

namespace sprout {
	namespace detail {
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
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_next_generator_test<T>::test(0))>::type>
		struct has_mem_next_generator
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_next_generator
			: public sprout::identity<decltype(sprout::detail::has_mem_next_generator_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_next_generator
			: public sprout::bool_constant<
				sprout::detail::has_mem_next_generator<T const>::value
			>
		{};

		template<typename Gen, typename = void>
		struct get_next_generator_impl;

		template<typename Gen>
		struct get_next_generator_impl<
			Gen,
			typename std::enable_if<
				std::is_lvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& sprout::detail::is_substitutable_const_next_generator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().next_generator())
			get_next_generator(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().next_generator())
			{
				typedef decltype(std::declval<Gen>().next_generator()) type;
				return sprout::const_reference_cast<type>(sprout::as_const(gen).next_generator());
			}
		};
		template<typename Gen>
		struct get_next_generator_impl<
			Gen,
			typename std::enable_if<
				std::is_lvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::is_substitutable_const_next_generator<Gen>::value
					&& sprout::detail::has_mem_next_generator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().next_generator())
			get_next_generator(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().next_generator())
			{
				return gen.next_generator();
			}
		};
		template<typename Gen>
		struct get_next_generator_impl<
			Gen,
			typename std::enable_if<
				std::is_lvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::is_substitutable_const_next_generator<Gen>::value
					&& !sprout::detail::has_mem_next_generator<Gen>::value
					&& sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>())
			get_next_generator(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>())
			{
				return gen;
			}
		};
		template<typename Gen>
		struct get_next_generator_impl<
			Gen,
			typename std::enable_if<
				std::is_lvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::is_substitutable_const_next_generator<Gen>::value
					&& !sprout::detail::has_mem_next_generator<Gen>::value
					&& !sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::tuples::get<1>(std::declval<Gen>()))
			get_next_generator(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::tuples::get<1>(std::declval<Gen>()))
			{
				return sprout::tuples::get<1>(gen);
			}
		};

		template<typename Gen>
		struct get_next_generator_impl<
			Gen,
			typename std::enable_if<
				std::is_rvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& sprout::detail::is_substitutable_const_next_generator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().next_generator())
			get_next_generator(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().next_generator())
			{
				typedef decltype(std::declval<Gen>().next_generator()) type;
				return sprout::const_reference_cast<type>(sprout::as_const(sprout::move(gen)).next_generator());
			}
		};
		template<typename Gen>
		struct get_next_generator_impl<
			Gen,
			typename std::enable_if<
				std::is_rvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::is_substitutable_const_next_generator<Gen>::value
					&& sprout::detail::has_mem_next_generator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().next_generator())
			get_next_generator(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().next_generator())
			{
				return sprout::move(gen).next_generator();
			}
		};
		template<typename Gen>
		struct get_next_generator_impl<
			Gen,
			typename std::enable_if<
				std::is_rvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::is_substitutable_const_next_generator<Gen>::value
					&& !sprout::detail::has_mem_next_generator<Gen>::value
					&& sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>())
			get_next_generator(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>())
			{
				return sprout::move(gen);
			}
		};
		template<typename Gen>
		struct get_next_generator_impl<
			Gen,
			typename std::enable_if<
				std::is_rvalue_reference<Gen>::value && !std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::is_substitutable_const_next_generator<Gen>::value
					&& !sprout::detail::has_mem_next_generator<Gen>::value
					&& !sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::tuples::get<1>(std::declval<Gen>()))
			get_next_generator(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::tuples::get<1>(std::declval<Gen>()))
			{
				return sprout::tuples::get<1>(sprout::move(gen));
			}
		};

		template<typename Gen>
		struct get_next_generator_impl<
			Gen,
			typename std::enable_if<
				std::is_reference<Gen>::value && std::is_const<typename std::remove_reference<Gen>::type>::value
					&& sprout::detail::has_mem_next_generator<Gen const>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>().next_generator())
			get_next_generator(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>().next_generator())
			{
				return gen.next_generator();
			}
		};
		template<typename Gen>
		struct get_next_generator_impl<
			Gen,
			typename std::enable_if<
				std::is_reference<Gen>::value && std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_next_generator<Gen const>::value
					&& sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(std::declval<Gen>())
			get_next_generator(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(std::declval<Gen>())
			{
				return gen;
			}
		};
		template<typename Gen>
		struct get_next_generator_impl<
			Gen,
			typename std::enable_if<
				std::is_reference<Gen>::value && std::is_const<typename std::remove_reference<Gen>::type>::value
					&& !sprout::detail::has_mem_next_generator<Gen const>::value
					&& !sprout::is_input_iterator<Gen>::value
			>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::tuples::get<1>(std::declval<Gen>()))
			get_next_generator(Gen gen)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::tuples::get<1>(std::declval<Gen>()))
			{
				return sprout::tuples::get<1>(gen);
			}
		};
	}	// namespace detail
}	// namespace sprout

namespace sprout_generator_detail {
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::detail::get_next_generator_impl<Gen&>::get_next_generator(std::declval<Gen&>()))
	get_next_generator(Gen& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::detail::get_next_generator_impl<Gen&>::get_next_generator(std::declval<Gen&>()))
	{
		return sprout::detail::get_next_generator_impl<Gen&>::get_next_generator(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(sprout::detail::get_next_generator_impl<Gen&&>::get_next_generator(std::declval<Gen&&>()))
	>::type
	get_next_generator(Gen&& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::detail::get_next_generator_impl<Gen&&>::get_next_generator(std::declval<Gen&&>()))
	{
		return sprout::detail::get_next_generator_impl<Gen&&>::get_next_generator(sprout::move(gen));
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::detail::get_next_generator_impl<Gen const&>::get_next_generator(std::declval<Gen const&>()))
	get_next_generator(Gen const& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::detail::get_next_generator_impl<Gen const&>::get_next_generator(std::declval<Gen const&>()))
	{
		return sprout::detail::get_next_generator_impl<Gen const&>::get_next_generator(gen);
	}
}	// namespace sprout_generator_detail

#endif	// #ifndef SPROUT_GENERATOR_DETAIL_NEXT_GENERATOR_HPP
