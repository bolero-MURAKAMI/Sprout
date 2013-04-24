#ifndef SPROUT_TYPE_TRAITS_ALIASES_HPP
#define SPROUT_TYPE_TRAITS_ALIASES_HPP

#include <sprout/config.hpp>
#if SPROUT_USE_TEMPLATE_ALIASES
#	include <cstddef>
#	include <type_traits>
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

namespace sprout {
#if SPROUT_USE_TEMPLATE_ALIASES
	// Copyright (c) 2011 osyo-manga : http://d.hatena.ne.jp/osyo-manga/

	//
	// Const-volatility specifiers
	//
	template<typename T>
	using remove_const_t = typename std::remove_const<T>::type;
	template<typename T>
	using remove_volatile_t = typename std::remove_volatile<T>::type;
	template<typename T>
	using remove_cv_t = typename std::remove_cv<T>::type;
	template<typename T>
	using add_const_t = typename std::add_const<T>::type;
	template<typename T>
	using add_volatile_t = typename std::add_volatile<T>::type;
	template<typename T>
	using add_cv_t = typename std::add_cv<T>::type;

	//
	// References
	//
	template<typename T>
	using remove_reference_t = typename std::remove_reference<T>::type;
	template<typename T>
	using add_lvalue_reference_t = typename std::add_lvalue_reference<T>::type;
	template<typename T>
	using add_rvalue_reference_t = typename std::add_rvalue_reference<T>::type;

	//
	// Pointers
	//
	template<typename T>
	using remove_pointer_t = typename std::remove_pointer<T>::type;
	template<typename T>
	using add_pointer_t = typename std::add_pointer<T>::type;

	//
	// Sign modifiers
	//
	template<typename T>
	using make_signed_t = typename std::make_signed<T>::type;
	template<typename T>
	using make_unsigned_t = typename std::make_unsigned<T>::type;

	//
	// Arrays
	//
	template<typename T>
	using remove_extent_t = typename std::remove_extent<T>::type;
	template<typename T>
	using remove_all_extents_t = typename std::remove_all_extents<T>::type;

	//
	// Miscellaneous transformations
	//
	template<
		std::size_t Len,
		std::size_t Align = std::alignment_of<typename std::aligned_storage<Len>::type>::value
	>
	using aligned_storage_t = typename std::aligned_storage<Len, Align>::type;
	// ???
	//template<std::size_t Len, typename... Types>
	//using aligned_union_t = typename std::aligned_union<Len, Types...>::type;
	template<typename T>
	using decay_t = typename std::decay<T>::type;
	template<bool B, typename T = void>
	using enable_if_t = typename std::enable_if<B, T>::type;
	template<bool B, typename T, typename F>
	using conditional_t = typename std::conditional<B, T, F>::type;
	template<typename... Types>
	using common_type_t = typename std::common_type<Types...>::type;
	template<typename T>
	using underlying_type_t = typename std::underlying_type<T>::type;
	template<typename F, typename... ArgTypes>
	using result_of_t = typename std::result_of<F(ArgTypes...)>::type;


	//
	// Const-volatility specifiers
	//
	template<typename T>
	using remove_const = sprout::remove_const_t<T>;
	template<typename T>
	using remove_volatile = sprout::remove_volatile_t<T>;
	template<typename T>
	using remove_cv = sprout::remove_cv_t<T>;
	template<typename T>
	using add_const = sprout::add_const_t<T>;
	template<typename T>
	using add_volatile = sprout::add_volatile_t<T>;
	template<typename T>
	using add_cv = sprout::add_cv_t<T>;

	//
	// References
	//
	template<typename T>
	using remove_reference = sprout::remove_reference_t<T>;
	template<typename T>
	using add_lvalue_reference = sprout::add_lvalue_reference_t<T>;
	template<typename T>
	using add_rvalue_reference = sprout::add_rvalue_reference_t<T>;

	//
	// Pointers
	//
	template<typename T>
	using remove_pointer = sprout::remove_pointer_t<T>;
	template<typename T>
	using add_pointer = sprout::add_pointer_t<T>;

	//
	// Sign modifiers
	//
	template<typename T>
	using make_signed = sprout::make_signed_t<T>;
	template<typename T>
	using make_unsigned = sprout::make_unsigned_t<T>;

	//
	// Arrays
	//
	template<typename T>
	using remove_extent = sprout::remove_extent_t<T>;
	template<typename T>
	using remove_all_extents = sprout::remove_all_extents_t<T>;

	//
	// Miscellaneous transformations
	//
	template<
		std::size_t Len,
		std::size_t Align = std::alignment_of<typename std::aligned_storage<Len>::type>::value
	>
	using aligned_storage = sprout::aligned_storage_t<Len, Align>;
	// ???
	//template<std::size_t Len, typename... Types>
	//using aligned_union = sprout::aligned_union_t<Len, Types...>;
	template<typename T>
	using decay = sprout::decay_t<T>;
	template<bool B, typename T = void>
	using enable_if = sprout::enable_if_t<B, T>;
	template<bool B, typename T, typename F>
	using conditional = sprout::conditional_t<B, T, F>;
	template<typename... Types>
	using common_type = sprout::common_type_t<Types...>;
	template<typename T>
	using underlying_type = sprout::underlying_type_t<T>;
	// ???
	//template<typename F, typename... ArgTypes>
	//using result_of = sprout::result_of_t<F, ArgTypes...>;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_ALIASES_HPP
