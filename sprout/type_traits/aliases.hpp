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
	using remove_const_ = typename std::remove_const<T>::type;
	template<typename T>
	using remove_volatile_ = typename std::remove_volatile<T>::type;
	template<typename T>
	using remove_cv_ = typename std::remove_cv<T>::type;
	template<typename T>
	using add_const_ = typename std::add_const<T>::type;
	template<typename T>
	using add_volatile_ = typename std::add_volatile<T>::type;
	template<typename T>
	using add_cv_ = typename std::add_cv<T>::type;

	//
	// References
	//
	template<typename T>
	using remove_reference_ = typename std::remove_reference<T>::type;
	template<typename T>
	using add_lvalue_reference_ = typename std::add_lvalue_reference<T>::type;
	template<typename T>
	using add_rvalue_reference_ = typename std::add_rvalue_reference<T>::type;

	//
	// Pointers
	//
	template<typename T>
	using remove_pointer_ = typename std::remove_pointer<T>::type;
	template<typename T>
	using add_pointer_ = typename std::add_pointer<T>::type;

	//
	// Sign modifiers
	//
	template<typename T>
	using make_signed_ = typename std::make_signed<T>::type;
	template<typename T>
	using make_unsigned_ = typename std::make_unsigned<T>::type;

	//
	// Arrays
	//
	template<typename T>
	using remove_extent_ = typename std::remove_extent<T>::type;
	template<typename T>
	using remove_all_extents_ = typename std::remove_all_extents<T>::type;

	//
	// Miscellaneous transformations
	//
	template<
		std::size_t Len,
		std::size_t Align = std::alignment_of<typename std::aligned_storage<Len>::type>::value
	>
	using aligned_storage_ = typename std::aligned_storage<Len, Align>::type;
	// !!!
	//template<std::size_t Len, typename... Types>
	//using aligned_union_ = typename std::aligned_union<Len, Types...>::type;
	template<typename T>
	using decay_ = typename std::decay<T>::type;
	template<bool B, typename T = void>
	using enable_if_ = typename std::enable_if<B, T>::type;
	template<bool B, typename T, typename F>
	using conditional_ = typename std::conditional<B, T, F>::type;
	template<typename... Types>
	using common_type_ = typename std::common_type<Types...>::type;
	template<typename T>
	using underlying_type_ = typename std::underlying_type<T>::type;
	template<typename F, typename... ArgTypes>
	using result_of_ = typename std::result_of<F(ArgTypes...)>::type;


	//
	// Const-volatility specifiers
	//
	template<typename T>
	using remove_const = sprout::remove_const_<T>;
	template<typename T>
	using remove_volatile = sprout::remove_volatile_<T>;
	template<typename T>
	using remove_cv = sprout::remove_cv_<T>;
	template<typename T>
	using add_const = sprout::add_const_<T>;
	template<typename T>
	using add_volatile = sprout::add_volatile_<T>;
	template<typename T>
	using add_cv = sprout::add_cv_<T>;

	//
	// References
	//
	template<typename T>
	using remove_reference = sprout::remove_reference_<T>;
	template<typename T>
	using add_lvalue_reference = sprout::add_lvalue_reference_<T>;
	template<typename T>
	using add_rvalue_reference = sprout::add_rvalue_reference_<T>;

	//
	// Pointers
	//
	template<typename T>
	using remove_pointer = sprout::remove_pointer_<T>;
	template<typename T>
	using add_pointer = sprout::add_pointer_<T>;

	//
	// Sign modifiers
	//
	template<typename T>
	using make_signed = sprout::make_signed_<T>;
	template<typename T>
	using make_unsigned = sprout::make_unsigned_<T>;

	//
	// Arrays
	//
	template<typename T>
	using remove_extent = sprout::remove_extent_<T>;
	template<typename T>
	using remove_all_extents = sprout::remove_all_extents_<T>;

	//
	// Miscellaneous transformations
	//
	template<
		std::size_t Len,
		std::size_t Align = std::alignment_of<typename std::aligned_storage<Len>::type>::value
	>
	using aligned_storage = sprout::aligned_storage_<Len, Align>;
	// !!!
	//template<std::size_t Len, typename... Types>
	//using aligned_union = sprout::aligned_union_<Len, Types...>;
	template<typename T>
	using decay = sprout::decay_<T>;
	template<bool B, typename T = void>
	using enable_if = sprout::enable_if_<B, T>;
	template<bool B, typename T, typename F>
	using conditional = sprout::conditional_<B, T, F>;
	template<typename... Types>
	using common_type = sprout::common_type_<Types...>;
	template<typename T>
	using underlying_type = sprout::underlying_type_<T>;
	template<typename F, typename... ArgTypes>
	using result_of = sprout::result_of_<F, ArgTypes...>;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_ALIASES_HPP
