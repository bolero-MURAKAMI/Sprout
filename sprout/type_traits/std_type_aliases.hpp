/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_STD_TYPE_ALIASES_HPP
#define SPROUT_TYPE_TRAITS_STD_TYPE_ALIASES_HPP

#include <sprout/config.hpp>
#if SPROUT_USE_TEMPLATE_ALIASES
#	include <cstddef>
#	include <sprout/type_traits/std_type_traits.hpp>
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

namespace sprout {
#if SPROUT_USE_TEMPLATE_ALIASES
	// Copyright (c) 2011 osyo-manga : http://d.hatena.ne.jp/osyo-manga/

	// 20.10.7.1 Const-volatile modifications

	template<typename T>
	using remove_const_t = typename sprout::remove_const<T>::type;
	template<typename T>
	using remove_volatile_t = typename sprout::remove_volatile<T>::type;
	template<typename T>
	using remove_cv_t = typename sprout::remove_cv<T>::type;
	template<typename T>
	using add_const_t = typename sprout::add_const<T>::type;
	template<typename T>
	using add_volatile_t = typename sprout::add_volatile<T>::type;
	template<typename T>
	using add_cv_t = typename sprout::add_cv<T>::type;

	// 20.10.7.2 Reference modifications

	template<typename T>
	using remove_reference_t = typename sprout::remove_reference<T>::type;
	template<typename T>
	using add_lvalue_reference_t = typename sprout::add_lvalue_reference<T>::type;
	template<typename T>
	using add_rvalue_reference_t = typename sprout::add_rvalue_reference<T>::type;

	// 20.10.7.3 Sign modifications

	template<typename T>
	using make_signed_t = typename sprout::make_signed<T>::type;
	template<typename T>
	using make_unsigned_t = typename sprout::make_unsigned<T>::type;

	// 20.10.7.4 Array modifications

	template<typename T>
	using remove_extent_t = typename sprout::remove_extent<T>::type;
	template<typename T>
	using remove_all_extents_t = typename sprout::remove_all_extents<T>::type;

	// 20.10.7.5 Pointer modifications

	template<typename T>
	using remove_pointer_t = typename sprout::remove_pointer<T>::type;
	template<typename T>
	using add_pointer_t = typename sprout::add_pointer<T>::type;

	// 20.10.7.6 Other transformations

	template<
		std::size_t Len,
		std::size_t Align = sprout::alignment_of<typename sprout::aligned_storage<Len>::type>::value
	>
	using aligned_storage_t = typename sprout::aligned_storage<Len, Align>::type;
	template<std::size_t Len, typename... Types>
	using aligned_union_t = typename sprout::aligned_union<Len, Types...>::type;
	template<typename T>
	using decay_t = typename sprout::decay<T>::type;
	template<bool B, typename T = void>
	using enable_if_t = typename sprout::enable_if<B, T>::type;
	template<bool B, typename T, typename F>
	using conditional_t = typename sprout::conditional<B, T, F>::type;
	template<typename... Types>
	using common_type_t = typename sprout::common_type<Types...>::type;
	template<typename T>
	using underlying_type_t = typename sprout::underlying_type<T>::type;
	template<typename F, typename... ArgTypes>
	using result_of_t = typename sprout::result_of<F(ArgTypes...)>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_STD_TYPE_ALIASES_HPP
