/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_HAS_XXX_HPP
#define SPROUT_TYPE_TRAITS_HAS_XXX_HPP

#include <sprout/config.hpp>
#include <sprout/preprocessor/cat.hpp>
#include <sprout/type_traits/integral_constant.hpp>

//
// SPROUT_HAS_XXX_TYPE_DEF
// SPROUT_HAS_XXX_TYPE_DEF_LAZY
//
#if defined(_MSC_VER)
#define SPROUT_HAS_XXX_TYPE_DEF(NAME, TYPE) \
	template<typename T, typename = typename T::TYPE> \
	sprout::true_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TYPE), NAME), __LINE__)(int); \
	template<typename T> \
	sprout::false_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TYPE), NAME), __LINE__)(long); \
	template<typename T, typename Base_ = decltype(SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TYPE), NAME), __LINE__)<T>(0))> \
	struct NAME \
		: public Base_ \
	{}
#else
#define SPROUT_HAS_XXX_TYPE_DEF(NAME, TYPE) \
	template<typename T, typename = typename T::TYPE> \
	sprout::true_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TYPE), NAME), __LINE__)(int); \
	template<typename T> \
	sprout::false_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TYPE), NAME), __LINE__)(long); \
	template<typename T> \
	struct NAME \
		: public decltype(SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TYPE), NAME), __LINE__)<T>(0)) \
	{}
#endif
#define SPROUT_HAS_XXX_TYPE_DEF_LAZY(TYPE) \
	SPROUT_HAS_XXX_TYPE_DEF(SPROUT_PP_CAT(has_, TYPE), TYPE)

//
// SPROUT_HAS_XXX_VALUE_DEF
// SPROUT_HAS_XXX_VALUE_DEF_LAZY
//
#if defined(_MSC_VER)
#define SPROUT_HAS_XXX_VALUE_DEF(NAME, VALUE) \
	template<typename T, decltype(&T::VALUE) = &T::VALUE> \
	sprout::true_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_value_, VALUE), NAME), __LINE__)(int); \
	template<typename T> \
	sprout::false_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_value_, VALUE), NAME), __LINE__)(long); \
	template<typename T, typename Base_ = decltype(SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_value_, VALUE), NAME), __LINE__)<T>(0))> \
	struct NAME \
		: public Base_ \
	{}
#else
#define SPROUT_HAS_XXX_VALUE_DEF(NAME, VALUE) \
	template<typename T, decltype(&T::VALUE) = &T::VALUE> \
	sprout::true_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_value_, VALUE), NAME), __LINE__)(int); \
	template<typename T> \
	sprout::false_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_value_, VALUE), NAME), __LINE__)(long); \
	template<typename T> \
	struct NAME \
		: public decltype(SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_value_, VALUE), NAME), __LINE__)<T>(0)) \
	{}
#endif
#define SPROUT_HAS_XXX_VALUE_DEF_LAZY(VALUE) \
	SPROUT_HAS_XXX_VALUE_DEF(SPROUT_PP_CAT(has_, VALUE), VALUE)

//
// SPROUT_HAS_XXX_TEMPLATE_DEF
// SPROUT_HAS_XXX_TEMPLATE_DEF_LAZY
//
#if defined(_MSC_VER)
#define SPROUT_HAS_XXX_TEMPLATE_DEF(NAME, TEMPLATE) \
	template<typename T, template<typename...> class = T::template TEMPLATE> \
	sprout::true_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TEMPLATE), NAME), __LINE__)(int); \
	template<typename T> \
	sprout::false_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TEMPLATE), NAME), __LINE__)(long); \
	template<typename T, typename Base_ = decltype(SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TEMPLATE), NAME), __LINE__)<T>(0))> \
	struct NAME \
		: public Base_ \
	{}
#else
#define SPROUT_HAS_XXX_TEMPLATE_DEF(NAME, TEMPLATE) \
	template<typename T, template<typename...> class = T::template TEMPLATE> \
	sprout::true_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TEMPLATE), NAME), __LINE__)(int); \
	template<typename T> \
	sprout::false_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TEMPLATE), NAME), __LINE__)(long); \
	template<typename T> \
	struct NAME \
		: public decltype(SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TEMPLATE), NAME), __LINE__)<T>(0)) \
	{}
#endif
#define SPROUT_HAS_XXX_TEMPLATE_DEF_LAZY(TEMPLATE) \
	SPROUT_HAS_XXX_TEMPLATE_DEF(SPROUT_PP_CAT(has_, TEMPLATE), TEMPLATE)

#endif	// #ifndef SPROUT_TYPE_TRAITS_HAS_XXX_HPP
