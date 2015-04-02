/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_STD_TYPE_TRAITS_HPP
#define SPROUT_TYPE_TRAITS_STD_TYPE_TRAITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/detail/predef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/common_type.hpp>
#include <sprout/type_traits/is_signed.hpp>
#include <sprout/type_traits/is_unsigned.hpp>
#include <sprout/type_traits/is_destructible.hpp>
#include <sprout/type_traits/is_nothrow_destructible.hpp>
#include <sprout/type_traits/result_of.hpp>
#include <sprout/type_traits/is_null_pointer.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>
#if !defined(_LIBCPP_VERSION) || (_LIBCPP_VERSION < 1101)
#	include <sprout/tpp/algorithm/max_element.hpp>
#endif

namespace sprout {

	// 20.10.4.1 Primary type categories

	template<typename T>
	struct is_void
		: public sprout::detail::type_traits_wrapper<std::is_void<T> >
	{};
	template<typename T>
	struct is_integral
		: public sprout::detail::type_traits_wrapper<std::is_integral<T> >
	{};
	template<typename T>
	struct is_floating_point
		: public sprout::detail::type_traits_wrapper<std::is_floating_point<T> >
	{};
	template<typename T>
	struct is_array
		: public sprout::detail::type_traits_wrapper<std::is_array<T> >
	{};
	template<typename T>
	struct is_pointer
		: public sprout::detail::type_traits_wrapper<std::is_pointer<T> >
	{};
	template<typename T>
	struct is_lvalue_reference
		: public sprout::detail::type_traits_wrapper<std::is_lvalue_reference<T> >
	{};
	template<typename T>
	struct is_rvalue_reference
		: public sprout::detail::type_traits_wrapper<std::is_rvalue_reference<T> >
	{};
	template<typename T>
	struct is_member_object_pointer
		: public sprout::detail::type_traits_wrapper<std::is_member_object_pointer<T> >
	{};
	template<typename T>
	struct is_member_function_pointer
		: public sprout::detail::type_traits_wrapper<std::is_member_function_pointer<T> >
	{};
	template<typename T>
	struct is_enum
		: public sprout::detail::type_traits_wrapper<std::is_enum<T> >
	{};
	template<typename T>
	struct is_union
		: public sprout::detail::type_traits_wrapper<std::is_union<T> >
	{};
	template<typename T>
	struct is_class
		: public sprout::detail::type_traits_wrapper<std::is_class<T> >
	{};
	template<typename T>
	struct is_function
		: public sprout::detail::type_traits_wrapper<std::is_function<T> >
	{};

	// 20.10.4.2 Composite type traits

	template<typename T>
	struct is_reference
		: public sprout::detail::type_traits_wrapper<std::is_reference<T> >
	{};
	template<typename T>
	struct is_arithmetic
		: public sprout::detail::type_traits_wrapper<std::is_arithmetic<T> >
	{};
	template<typename T>
	struct is_fundamental
		: public sprout::detail::type_traits_wrapper<std::is_fundamental<T> >
	{};
	template<typename T>
	struct is_object
		: public sprout::detail::type_traits_wrapper<std::is_object<T> >
	{};
	template<typename T>
	struct is_scalar
		: public sprout::detail::type_traits_wrapper<std::is_scalar<T> >
	{};
	template<typename T>
	struct is_compound
		: public sprout::detail::type_traits_wrapper<std::is_compound<T> >
	{};
	template<typename T>
	struct is_member_pointer
		: public sprout::detail::type_traits_wrapper<std::is_member_pointer<T> >
	{};

	// 20.10.4.3 Type properties

	template<typename T>
	struct is_const
		: public sprout::detail::type_traits_wrapper<std::is_const<T> >
	{};
	template<typename T>
	struct is_volatile
		: public sprout::detail::type_traits_wrapper<std::is_volatile<T> >
	{};
	template<typename T>
	struct is_trivial
		: public sprout::detail::type_traits_wrapper<std::is_trivial<T> >
	{};
#if !defined(_LIBCPP_VERSION)
	template<typename T>
	struct is_trivially_copyable
		: public sprout::is_scalar<typename std::remove_all_extents<T>::type>
	{};
#else
	template<typename T>
	struct is_trivially_copyable
		: public sprout::detail::type_traits_wrapper<std::is_trivially_copyable<T> >
	{};
#endif
	template<typename T>
	struct is_standard_layout
		: public sprout::detail::type_traits_wrapper<std::is_standard_layout<T> >
	{};
	template<typename T>
	struct is_pod
		: public sprout::detail::type_traits_wrapper<std::is_pod<T> >
	{};
	template<typename T>
	struct is_literal_type
		: public sprout::detail::type_traits_wrapper<std::is_literal_type<T> >
	{};
	template<typename T>
	struct is_empty
		: public sprout::detail::type_traits_wrapper<std::is_empty<T> >
	{};
	template<typename T>
	struct is_polymorphic
		: public sprout::detail::type_traits_wrapper<std::is_polymorphic<T> >
	{};
	template<typename T>
	struct is_abstract
		: public sprout::detail::type_traits_wrapper<std::is_abstract<T> >
	{};
//	template<typename T>
//	struct is_signed
//		: public sprout::detail::type_traits_wrapper<std::is_signed<T> >
//	{};
//	template<typename T>
//	struct is_unsigned
//		: public sprout::detail::type_traits_wrapper<std::is_unsigned<T> >
//	{};
	template<typename T, typename... Args>
	struct is_constructible
		: public sprout::detail::type_traits_wrapper<std::is_constructible<T, Args...> >
	{};
	template<typename T>
	struct is_default_constructible
		: public sprout::detail::type_traits_wrapper<std::is_default_constructible<T> >
	{};
	template<typename T>
	struct is_copy_constructible
		: public sprout::detail::type_traits_wrapper<std::is_copy_constructible<T> >
	{};
	template<typename T>
	struct is_move_constructible
		: public sprout::detail::type_traits_wrapper<std::is_move_constructible<T> >
	{};
	template<typename T, typename U>
	struct is_assignable
		: public sprout::detail::type_traits_wrapper<std::is_assignable<T, U> >
	{};
	template<typename T>
	struct is_copy_assignable
		: public sprout::detail::type_traits_wrapper<std::is_copy_assignable<T> >
	{};
	template<typename T>
	struct is_move_assignable
		: public sprout::detail::type_traits_wrapper<std::is_move_assignable<T> >
	{};
//	template<typename T>
//	struct is_destructible
//		: public sprout::detail::type_traits_wrapper<std::is_destructible<T> >
//	{};
#if !defined(_LIBCPP_VERSION)
#if SPROUT_CLANG_HAS_FUTURE(is_trivially_constructible)
	template<typename T, typename... Args>
	struct is_trivially_constructible
		: public sprout::bool_constant<__is_trivially_constructible(T, Args...)>
	{};
#else	// #if SPROUT_CLANG_HAS_FUTURE(is_trivially_constructible)
	template<typename T, typename... Args>
	struct is_trivially_constructible
		: public sprout::false_type
	{};
#if SPROUT_CLANG_HAS_FUTURE(has_trivial_constructor) || SPROUT_GCC_OR_LATER(4, 3, 0)
	template<typename T>
	struct is_trivially_constructible<T>
		: public sprout::bool_constant<__has_trivial_constructor(T)>
	{};
#else	// #if SPROUT_CLANG_HAS_FUTURE(has_trivial_constructor) || SPROUT_GCC_OR_LATER(4, 3, 0)
	template<typename T>
	struct is_trivially_constructible<T>
		: public sprout::is_scalar<T>
	{};
#endif	// #if SPROUT_CLANG_HAS_FUTURE(has_trivial_constructor) || SPROUT_GCC_OR_LATER(4, 3, 0)
	template<typename T>
	struct is_trivially_constructible<T, T&>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_constructible<T, T const&>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_constructible<T, T&&>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_constructible<T, T const&&>
		: public sprout::is_scalar<T>
	{};
#endif	// #if SPROUT_CLANG_HAS_FUTURE(is_trivially_constructible)
	template<typename T>
	struct is_trivially_default_constructible
		: public sprout::is_trivially_constructible<T>
	{};
	template<typename T>
	struct is_trivially_copy_constructible
		: public sprout::is_trivially_constructible<T, typename std::add_lvalue_reference<T>::type const>
	{};
	template<typename T>
	struct is_trivially_move_constructible
		: public sprout::is_trivially_constructible<T, typename std::add_rvalue_reference<T>::type const>
	{};
#if SPROUT_CLANG_HAS_FUTURE(is_trivially_assignable)
	template<typename T, typename U>
	struct is_trivially_assignable
		: public sprout::bool_constant<__is_trivially_assignable(T, U)>
	{};
#else	// #if SPROUT_CLANG_HAS_FUTURE(is_trivially_assignable)
	template<typename T, typename U>
	struct is_trivially_assignable
		: public sprout::false_type
	{};
	template<typename T>
	struct is_trivially_assignable<T&, T>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_assignable<T&, T&>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_assignable<T&, T const&>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_assignable<T&, T&&>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_assignable<T&, T const&&>
		: public sprout::is_scalar<T>
	{};
#endif	// #if SPROUT_CLANG_HAS_FUTURE(is_trivially_assignable)
	template<typename T>
	struct is_trivially_copy_assignable
		: public sprout::is_trivially_assignable<
			typename std::add_lvalue_reference<T>::type,
			typename std::add_lvalue_reference<T>::type const
		>
	{};
	template<typename T>
	struct is_trivially_move_assignable
		: public sprout::is_trivially_assignable<
			typename std::add_lvalue_reference<T>::type,
			typename std::add_rvalue_reference<T>::type
		>
	{};
#else	// #if !defined(_LIBCPP_VERSION)
	template<typename T, typename... Args>
	struct is_trivially_constructible
		: public sprout::detail::type_traits_wrapper<std::is_trivially_constructible<T, Args...> >
	{};
	template<typename T>
	struct is_trivially_default_constructible
		: public sprout::detail::type_traits_wrapper<std::is_trivially_default_constructible<T> >
	{};
	template<typename T>
	struct is_trivially_copy_constructible
		: public sprout::detail::type_traits_wrapper<std::is_trivially_copy_constructible<T> >
	{};
	template<typename T>
	struct is_trivially_move_constructible
		: public sprout::detail::type_traits_wrapper<std::is_trivially_move_constructible<T> >
	{};
	template<typename T, typename U>
	struct is_trivially_assignable
		: public sprout::detail::type_traits_wrapper<std::is_trivially_assignable<T, U> >
	{};
	template<typename T>
	struct is_trivially_copy_assignable
		: public sprout::detail::type_traits_wrapper<std::is_trivially_copy_assignable<T> >
	{};
	template<typename T>
	struct is_trivially_move_assignable
		: public sprout::detail::type_traits_wrapper<std::is_trivially_move_assignable<T> >
	{};
#endif	// #if !defined(_LIBCPP_VERSION)
#if !defined(_LIBCPP_VERSION) && SPROUT_GCC_EARLIER(4, 8, 0)
#if SPROUT_CLANG_HAS_FUTURE(has_trivial_destructor) || SPROUT_GCC_OR_LATER(4, 3, 0)
	template<typename T>
	struct is_trivially_destructible
		: public sprout::bool_constant<sprout::is_destructible<T>::value && __has_trivial_destructor(T)>
	{};
#else	// #if SPROUT_CLANG_HAS_FUTURE(has_trivial_destructor) || SPROUT_GCC_OR_LATER(4, 3, 0)
	template<typename T>
	struct is_trivially_destructible
		: public sprout::bool_constant<
			sprout::is_destructible<T>::value
			&& (std::is_scalar<typename std::remove_all_extents<T>::type>::value
				|| std::is_reference<typename std::remove_all_extents<T>::type>::value
				)
		>
	{};
#endif	// #if SPROUT_CLANG_HAS_FUTURE(has_trivial_destructor) || SPROUT_GCC_OR_LATER(4, 3, 0)
#else	// #if !defined(_LIBCPP_VERSION) && SPROUT_GCC_EARLIER(4, 8, 0)
	template<typename T>
	struct is_trivially_destructible
		: public sprout::detail::type_traits_wrapper<std::is_trivially_destructible<T> >
	{};
#endif	// #if !defined(_LIBCPP_VERSION) && SPROUT_GCC_EARLIER(4, 8, 0)
	template<typename T, typename... Args>
	struct is_nothrow_constructible
		: public sprout::detail::type_traits_wrapper<std::is_nothrow_constructible<T, Args...> >
	{};
	template<typename T>
	struct is_nothrow_default_constructible
		: public sprout::detail::type_traits_wrapper<std::is_nothrow_default_constructible<T> >
	{};
	template<typename T>
	struct is_nothrow_copy_constructible
		: public sprout::detail::type_traits_wrapper<std::is_nothrow_copy_constructible<T> >
	{};
	template<typename T>
	struct is_nothrow_move_constructible
		: public sprout::detail::type_traits_wrapper<std::is_nothrow_move_constructible<T> >
	{};
	template<typename T, typename U>
	struct is_nothrow_assignable
		: public sprout::detail::type_traits_wrapper<std::is_nothrow_assignable<T, U> >
	{};
	template<typename T>
	struct is_nothrow_copy_assignable
		: public sprout::detail::type_traits_wrapper<std::is_nothrow_copy_assignable<T> >
	{};
	template<typename T>
	struct is_nothrow_move_assignable
		: public sprout::detail::type_traits_wrapper<std::is_nothrow_move_assignable<T> >
	{};
//	template<typename T>
//	struct is_nothrow_destructible
//		: public sprout::detail::type_traits_wrapper<std::is_nothrow_destructible<T> >
//	{};
	template<typename T>
	struct has_virtual_destructor
		: public sprout::detail::type_traits_wrapper<std::has_virtual_destructor<T> >
	{};

	// 20.10.5 Type property queries

	template<typename T>
	struct alignment_of
		: public sprout::detail::type_traits_wrapper<std::alignment_of<T> >
	{};
	template<typename T>
	struct rank
		: public sprout::detail::type_traits_wrapper<std::rank<T> >
	{};
	template<typename T, unsigned I = 0>
	struct extent
		: public sprout::detail::type_traits_wrapper<std::extent<T, I> >
	{};

	// 20.10.6 Relationships between types

	template<typename T, typename U>
	struct is_same
		: public sprout::detail::type_traits_wrapper<std::is_same<T, U> >
	{};
	template<typename From, typename To>
	struct is_base_of
		: public sprout::detail::type_traits_wrapper<std::is_base_of<From, To> >
	{};
	template<typename From, typename To>
	struct is_convertible
		: public sprout::detail::type_traits_wrapper<std::is_convertible<From, To> >
	{};

	// 20.10.7.1 Const-volatile modifications

	using std::remove_const;
	using std::remove_volatile;
	using std::remove_cv;
	using std::add_const;
	using std::add_volatile;
	using std::add_cv;

	// 20.10.7.2 Reference modifications

	using std::remove_reference;
	using std::add_lvalue_reference;
	using std::add_rvalue_reference;

	// 20.10.7.3 Sign modifications

	using std::make_signed;
	using std::make_unsigned;

	// 20.10.7.4 Array modifications

	using std::remove_extent;
	using std::remove_all_extents;

	// 20.10.7.5 Pointer modifications

	using std::remove_pointer;
	using std::add_pointer;

	// 20.10.7.6 Other transformations

	using std::aligned_storage;
#if !defined(_LIBCPP_VERSION) || (_LIBCPP_VERSION < 1101)
	template<std::size_t Len, typename... Types>
	struct aligned_union
		: public std::aligned_storage<
			sprout::tpp::max_element_c<std::size_t, Len, sizeof(Types)...>::value,
			sprout::tpp::max_element_c<std::size_t, std::alignment_of<Types>::value...>::value
		>
	{};
#else	// #if !defined(_LIBCPP_VERSION) || (_LIBCPP_VERSION < 1101)
	using std::aligned_union;
#endif	// #if !defined(_LIBCPP_VERSION) || (_LIBCPP_VERSION < 1101)
	using std::decay;
	using std::enable_if;
	using std::conditional;
//	using std::common_type;
	using std::underlying_type;
//	using std::result_of;
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_STD_TYPE_TRAITS_HPP
