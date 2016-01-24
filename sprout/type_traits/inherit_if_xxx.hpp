/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_INHERIT_IF_XXX_HPP
#define SPROUT_TYPE_TRAITS_INHERIT_IF_XXX_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/preprocessor/cat.hpp>
#include <sprout/preprocessor/some_number.hpp>
#include <sprout/type_traits/has_xxx.hpp>
#if defined(_MSC_VER)
#	include <sprout/workaround/std/cstddef.hpp>
#endif

//
// SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF
// SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF_LAZY
//
#define SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF_IMPL(NAME, ALIAS, TYPE, NUM) \
	SPROUT_HAS_XXX_TYPE_DEF(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_inherit_if_xxx_type_def_impl_has_, TYPE), NUM), TYPE); \
	template<typename T, typename = void> \
	struct NAME {}; \
	template<typename T> \
	struct NAME< \
		T, \
		typename std::enable_if<SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_inherit_if_xxx_type_def_impl_has_, TYPE), NUM)<T>::value>::type \
	> { \
	public: \
		typedef typename T::TYPE ALIAS; \
	}
#define SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF(NAME, ALIAS, TYPE) \
	SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF_IMPL(NAME, ALIAS, TYPE, SPROUT_PP_SOME_NUMBER())
#define SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF_LAZY(ALIAS, TYPE) \
	SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF(SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(inherit_, ALIAS), _if_), TYPE), ALIAS, TYPE)

//
// SPROUT_INHERIT_IF_XXX_TYPE_DEF
// SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY
//
#define SPROUT_INHERIT_IF_XXX_TYPE_DEF(NAME, TYPE) \
	SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF(NAME, TYPE, TYPE)
#define SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(TYPE) \
	SPROUT_INHERIT_IF_XXX_TYPE_DEF(SPROUT_PP_CAT(inherit_if_, TYPE), TYPE)

//
// SPROUT_INHERIT_ALIAS_IF_XXX_CONSTANT_DEF
// SPROUT_INHERIT_ALIAS_IF_XXX_CONSTANT_DEF_LAZY
//
#if defined(_MSC_VER)
#define SPROUT_INHERIT_ALIAS_IF_XXX_CONSTANT_DEF_IMPL(NAME, ALIAS, CONSTANT, NUM) \
	SPROUT_HAS_XXX_VALUE_DEF(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_inherit_if_xxx_constant_def_impl_has_, CONSTANT), NUM), CONSTANT); \
	template<typename T, typename = void> \
	struct NAME {}; \
	template<typename T> \
	struct NAME< \
		T, \
		typename std::enable_if<SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_inherit_if_xxx_constant_def_impl_has_, CONSTANT), NUM)<T>::value>::type \
	> { \
	public: \
		SPROUT_STATIC_CONSTEXPR typename std::decay<decltype(T::CONSTANT)>::type/*std::size_t*/ ALIAS = T::CONSTANT; \
	};/* \
	template<typename T> \
	SPROUT_CONSTEXPR_OR_CONST std::size_t NAME< \
		T, \
		typename std::enable_if<SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_inherit_if_xxx_constant_def_impl_has_, CONSTANT), NUM)<T>::value>::type \
	>::ALIAS !!! */
#else
#define SPROUT_INHERIT_ALIAS_IF_XXX_CONSTANT_DEF_IMPL(NAME, ALIAS, CONSTANT, NUM) \
	SPROUT_HAS_XXX_VALUE_DEF(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_inherit_if_xxx_constant_def_impl_has_, CONSTANT), NUM), CONSTANT); \
	template<typename T, typename = void> \
	struct NAME {}; \
	template<typename T> \
	struct NAME< \
		T, \
		typename std::enable_if<SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_inherit_if_xxx_constant_def_impl_has_, CONSTANT), NUM)<T>::value>::type \
	> { \
	public: \
		SPROUT_STATIC_CONSTEXPR typename std::decay<decltype(T::CONSTANT)>::type ALIAS = T::CONSTANT; \
	}; \
	template<typename T> \
	SPROUT_CONSTEXPR_OR_CONST typename std::decay<decltype(T::CONSTANT)>::type NAME< \
		T, \
		typename std::enable_if<SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_inherit_if_xxx_constant_def_impl_has_, CONSTANT), NUM)<T>::value>::type \
	>::ALIAS
#endif
#define SPROUT_INHERIT_ALIAS_IF_XXX_CONSTANT_DEF(NAME, ALIAS, CONSTANT) \
	SPROUT_INHERIT_ALIAS_IF_XXX_CONSTANT_DEF_IMPL(NAME, ALIAS, CONSTANT, SPROUT_PP_SOME_NUMBER())
#define SPROUT_INHERIT_ALIAS_IF_XXX_CONSTANT_DEF_LAZY(ALIAS, CONSTANT) \
	SPROUT_INHERIT_ALIAS_IF_XXX_CONSTANT_DEF(SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(inherit_, ALIAS), _if_), CONSTANT), ALIAS, CONSTANT)

//
// SPROUT_INHERIT_IF_XXX_CONSTANT_DEF
// SPROUT_INHERIT_IF_XXX_CONSTANT_DEF_LAZY
//
#define SPROUT_INHERIT_IF_XXX_CONSTANT_DEF(NAME, CONSTANT) \
	SPROUT_INHERIT_ALIAS_IF_XXX_CONSTANT_DEF(NAME, CONSTANT, CONSTANT)
#define SPROUT_INHERIT_IF_XXX_CONSTANT_DEF_LAZY(CONSTANT) \
	SPROUT_INHERIT_IF_XXX_CONSTANT_DEF(SPROUT_PP_CAT(inherit_if_, CONSTANT), CONSTANT)

#endif	// #ifndef SPROUT_TYPE_TRAITS_INHERIT_IF_XXX_HPP
