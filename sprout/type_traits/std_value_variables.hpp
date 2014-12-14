/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_STD_VALUE_VARIABLES_HPP
#define SPROUT_TYPE_TRAITS_STD_VALUE_VARIABLES_HPP

#include <sprout/config.hpp>
#if SPROUT_USE_VARIABLE_TEMPLATES
#	include <sprout/workaround/std/cstddef.hpp>
#	include <sprout/type_traits/std_type_traits.hpp>
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES

namespace sprout {
#if SPROUT_USE_VARIABLE_TEMPLATES
	// 20.10.4.1 Primary type categories

	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_void_v = sprout::is_void<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_integral_v = sprout::is_integral<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_floating_point_v = sprout::is_floating_point<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_array_v = sprout::is_array<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_pointer_v = sprout::is_pointer<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_lvalue_reference_v = sprout::is_lvalue_reference<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_rvalue_reference_v = sprout::is_rvalue_reference<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_member_object_pointer_v = sprout::is_member_object_pointer<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_member_function_pointer_v = sprout::is_member_function_pointer<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_enum_v = sprout::is_enum<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_union_v = sprout::is_union<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_class_v = sprout::is_class<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_function_v = sprout::is_function<T>::value;

	// 20.10.4.2 Composite type traits

	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_reference_v = sprout::is_reference<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_arithmetic_v = sprout::is_arithmetic<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_fundamental_v = sprout::is_fundamental<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_object_v = sprout::is_object<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_scalar_v = sprout::is_scalar<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_compound_v = sprout::is_compound<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_member_pointer_v = sprout::is_member_pointer<T>::value;

	// 20.10.4.3 Type properties

	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_const_v = sprout::is_const<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_volatile_v = sprout::is_volatile<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_trivial_v = sprout::is_trivial<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_copyable_v = sprout::is_trivially_copyable<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_standard_layout_v = sprout::is_standard_layout<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_pod_v = sprout::is_pod<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_literal_type_v = sprout::is_literal_type<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_empty_v = sprout::is_empty<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_polymorphic_v = sprout::is_polymorphic<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_abstract_v = sprout::is_abstract<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_signed_v = sprout::is_signed<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_unsigned_v = sprout::is_unsigned<T>::value;
	template<typename T, typename... Args>
	SPROUT_STATIC_CONSTEXPR bool is_constructible_v = sprout::is_constructible<T, Args...>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_default_constructible_v = sprout::is_default_constructible<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_copy_constructible_v = sprout::is_copy_constructible<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_move_constructible_v = sprout::is_move_constructible<T>::value;
	template<typename T, typename U>
	SPROUT_STATIC_CONSTEXPR bool is_assignable_v = sprout::is_assignable<T, U>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_copy_assignable_v = sprout::is_copy_assignable<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_move_assignable_v = sprout::is_move_assignable<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_destructible_v = sprout::is_destructible<T>::value;
	template<typename T, typename... Args>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_constructible_v = sprout::is_trivially_constructible<T, Args...>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_default_constructible_v = sprout::is_trivially_default_constructible<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_copy_constructible_v = sprout::is_trivially_copy_constructible<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_move_constructible_v = sprout::is_trivially_move_constructible<T>::value;
	template<typename T, typename U>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_assignable_v = sprout::is_trivially_assignable<T, U>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_copy_assignable_v = sprout::is_trivially_copy_assignable<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_move_assignable_v = sprout::is_trivially_move_assignable<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_destructible_v = sprout::is_trivially_destructible<T>::value;
	template<typename T, typename... Args>
	SPROUT_STATIC_CONSTEXPR bool is_nothrow_constructible_v = sprout::is_nothrow_constructible<T, Args...>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_nothrow_default_constructible_v = sprout::is_nothrow_default_constructible<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_nothrow_copy_constructible_v = sprout::is_nothrow_copy_constructible<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_nothrow_move_constructible_v = sprout::is_nothrow_move_constructible<T>::value;
	template<typename T, typename U>
	SPROUT_STATIC_CONSTEXPR bool is_nothrow_assignable_v = sprout::is_nothrow_assignable<T, U>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_nothrow_copy_assignable_v = sprout::is_nothrow_copy_assignable<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_nothrow_move_assignable_v = sprout::is_nothrow_move_assignable<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_nothrow_destructible_v = sprout::is_nothrow_destructible<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool has_virtual_destructor_v = sprout::has_virtual_destructor<T>::value;

	// 20.10.5 Type property queries

	template<typename T>
	SPROUT_STATIC_CONSTEXPR std::size_t alignment_of_v = sprout::alignment_of<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR std::size_t rank_v = sprout::rank<T>::value;
	template<typename T, unsigned I = 0>
	SPROUT_STATIC_CONSTEXPR std::size_t extent_v = sprout::extent<T, I>::value;

	// 20.10.6 Relationships between types

	template<typename T, typename U>
	SPROUT_STATIC_CONSTEXPR bool is_same_v = sprout::is_same<T, U>::value;
	template<typename From, typename To>
	SPROUT_STATIC_CONSTEXPR bool is_base_of_v = sprout::is_base_of<From, To>::value;
	template<typename From, typename To>
	SPROUT_STATIC_CONSTEXPR bool is_convertible_v = sprout::is_convertible<From, To>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_STD_VALUE_VARIABLES_HPP
