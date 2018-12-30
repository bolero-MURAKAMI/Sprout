/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_HAS_XXX_HPP
#define SPROUT_TYPE_TRAITS_HAS_XXX_HPP

#include <type_traits>
#include <sprout/detail/one_type.hpp>
#include <sprout/preprocessor/cat.hpp>
#include <sprout/preprocessor/some_number.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/integral_constant.hpp>

#define SPROUT_HAS_XXX_DETAIL_NAME_GEN(PREFIX, ELEM, NAME, NUM) \
	SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(PREFIX, ELEM), NAME), NUM)

//
// SPROUT_HAS_XXX_TYPE_DEF
// SPROUT_HAS_XXX_TYPE_DEF_LAZY
//
#if defined(_MSC_VER) && (_MSC_VER > 1900)
#define SPROUT_HAS_XXX_TYPE_DEF_IMPL(NAME, TYPE, NUM) \
	template<typename T, typename = typename T::TYPE> \
	sprout::true_type SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_type_, TYPE, NAME, NUM)(int); \
	template<typename T> \
	sprout::false_type SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_type_, TYPE, NAME, NUM)(long); \
	template<typename T, typename Base_ = decltype(SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_type_, TYPE, NAME, NUM)<T>(0))> \
	struct NAME \
		: public Base_ \
	{}
#else
#define SPROUT_HAS_XXX_TYPE_DEF_IMPL(NAME, TYPE, NUM) \
	template<typename T, typename = typename T::TYPE> \
	sprout::true_type SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_type_, TYPE, NAME, NUM)(int); \
	template<typename T> \
	sprout::false_type SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_type_, TYPE, NAME, NUM)(long); \
	template<typename T> \
	struct NAME \
		: public sprout::identity<decltype(SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_type_, TYPE, NAME, NUM)<T>(0))>::type \
	{}
#endif
#define SPROUT_HAS_XXX_TYPE_DEF(NAME, TYPE) \
	SPROUT_HAS_XXX_TYPE_DEF_IMPL(NAME, TYPE, SPROUT_PP_SOME_NUMBER())
#define SPROUT_HAS_XXX_TYPE_DEF_LAZY(TYPE) \
	SPROUT_HAS_XXX_TYPE_DEF(SPROUT_PP_CAT(has_, TYPE), TYPE)

//
// SPROUT_HAS_XXX_VALUE_DEF
// SPROUT_HAS_XXX_VALUE_DEF_LAZY
//
#if defined(_MSC_VER)
#define SPROUT_HAS_XXX_VALUE_DEF_IMPL_HSD_OP(NAME, VALUE, NUM) \
	template<typename T> \
	struct SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_value_hsd_op_, VALUE, NAME, NUM) { \
	private: \
		template<typename U, typename V> \
		static sprout::detail::one_type check2(V*); \
		template<typename U, typename V> \
		static sprout::detail::not_one_type check2(U); \
	private: \
		template<typename U> \
		static typename std::enable_if< \
			sizeof(check2<U, decltype(U::VALUE)>(&U::VALUE)) == sizeof(sprout::detail::one_type), \
			sprout::detail::one_type \
		>::type has_matching_member(int); \
		template<typename U> \
		static sprout::detail::not_one_type has_matching_member(...); \
	private: \
		template<typename U> \
		struct ttc_sd \
			: public sprout::bool_constant<sizeof(has_matching_member<U>(0)) == sizeof(sprout::detail::one_type)> \
		{}; \
	public: \
		typedef typename ttc_sd<T>::type type; \
	}
#define SPROUT_HAS_XXX_VALUE_DEF_IMPL(NAME, VALUE, NUM) \
	SPROUT_HAS_XXX_VALUE_DEF_IMPL_HSD_OP(NAME, VALUE, NUM); \
	template<typename T> \
	struct NAME \
		: public std::conditional< \
 			std::is_class<T>::value, \
	 		SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_value_hsd_op_, VALUE, NAME, NUM)<T>, \
	 		sprout::false_type \
		>::type::type \
	{}
#else
#define SPROUT_HAS_XXX_VALUE_DEF_IMPL(NAME, VALUE, NUM) \
	template<typename T, typename sprout::identity<decltype(&T::VALUE)>::type = &T::VALUE> \
	sprout::true_type SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_value_, VALUE, NAME, NUM)(int); \
	template<typename T> \
	sprout::false_type SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_value_, VALUE, NAME, NUM)(long); \
	template<typename T> \
	struct NAME \
		: public sprout::identity<decltype(SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_value_, VALUE, NAME, NUM)<T>(0))>::type \
	{}
#endif
#define SPROUT_HAS_XXX_VALUE_DEF(NAME, VALUE) \
	SPROUT_HAS_XXX_VALUE_DEF_IMPL(NAME, VALUE, SPROUT_PP_SOME_NUMBER())
#define SPROUT_HAS_XXX_VALUE_DEF_LAZY(VALUE) \
	SPROUT_HAS_XXX_VALUE_DEF(SPROUT_PP_CAT(has_, VALUE), VALUE)

//
// SPROUT_HAS_XXX_TEMPLATE_DEF
// SPROUT_HAS_XXX_TEMPLATE_DEF_LAZY
//
#if defined(_MSC_VER) && (_MSC_VER > 1900)
#define SPROUT_HAS_XXX_TEMPLATE_DEF_IMPL(NAME, TEMPLATE, NUM) \
	template<typename T, template<typename...> class = T::template TEMPLATE> \
	sprout::true_type SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_type_, TEMPLATE, NAME, NUM)(int); \
	template<typename T> \
	sprout::false_type SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_type_, TEMPLATE, NAME, NUM)(long); \
	template<typename T, typename Base_ = decltype(SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_type_, TEMPLATE, NAME, NUM)<T>(0))> \
	struct NAME \
		: public Base_ \
	{}
#else
#define SPROUT_HAS_XXX_TEMPLATE_DEF_IMPL(NAME, TEMPLATE, NUM) \
	template<typename T, template<typename...> class = T::template TEMPLATE> \
	sprout::true_type SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_type_, TEMPLATE, NAME, NUM)(int); \
	template<typename T> \
	sprout::false_type SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_type_, TEMPLATE, NAME, NUM)(long); \
	template<typename T> \
	struct NAME \
		: public sprout::identity<decltype(SPROUT_HAS_XXX_DETAIL_NAME_GEN(sprout_has_xxx_impl_check_type_, TEMPLATE, NAME, NUM)<T>(0))>::type \
	{}
#endif
#define SPROUT_HAS_XXX_TEMPLATE_DEF(NAME, TEMPLATE) \
	SPROUT_HAS_XXX_TEMPLATE_DEF_IMPL(NAME, TEMPLATE, SPROUT_PP_SOME_NUMBER())
#define SPROUT_HAS_XXX_TEMPLATE_DEF_LAZY(TEMPLATE) \
	SPROUT_HAS_XXX_TEMPLATE_DEF(SPROUT_PP_CAT(has_, TEMPLATE), TEMPLATE)

#endif	// #ifndef SPROUT_TYPE_TRAITS_HAS_XXX_HPP
