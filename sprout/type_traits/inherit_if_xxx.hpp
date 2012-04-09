#ifndef SPROUT_TYPE_TRAITS_INHERIT_IF_XXX_HPP
#define SPROUT_TYPE_TRAITS_INHERIT_IF_XXX_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/preprocessor/cat.hpp>
#include <sprout/type_traits/has_xxx.hpp>

//
// SPROUT_INHERIT_IF_XXX_TYPE_DEF
//
#define SPROUT_INHERIT_IF_XXX_TYPE_DEF(NAME, TYPE) \
	SPROUT_HAS_XXX_TYPE_DEF(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_inherit_if_xxx_type_def_impl_has_, TYPE), __LINE__), TYPE); \
	template<typename T, typename Enable = void> \
	struct NAME {}; \
	template<typename T> \
	struct NAME< \
		T, \
		typename std::enable_if<SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_inherit_if_xxx_type_def_impl_has_, TYPE), __LINE__)<T>::value>::type \
	> { \
	public: \
		typedef typename T::TYPE TYPE; \
	}

//
// SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY
//
#define SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(TYPE) \
	SPROUT_INHERIT_IF_XXX_TYPE_DEF(SPROUT_PP_CAT(inherit_if_, TYPE), TYPE)

#endif	// #ifndef SPROUT_TYPE_TRAITS_INHERIT_IF_XXX_HPP
