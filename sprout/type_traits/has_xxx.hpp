#ifndef SPROUT_TYPE_TRAITS_HAS_XXX_HPP
#define SPROUT_TYPE_TRAITS_HAS_XXX_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/preprocessor/cat.hpp>

//
// SPROUT_HAS_XXX_TYPE_DEF
// SPROUT_HAS_XXX_TYPE_DEF_LAZY
//
#if defined(_MSC_VER)
#define SPROUT_HAS_XXX_TYPE_DEF(NAME, TYPE) \
	template<typename T, typename = typename T::TYPE> \
	std::true_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TYPE), NAME), __LINE__)(int); \
	template<typename T> \
	std::false_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TYPE), NAME), __LINE__)(long); \
	template<typename T, typename Base_ = decltype(SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TYPE), NAME), __LINE__)<T>(0))> \
	struct NAME \
		: public Base_ \
	{}
#else
#define SPROUT_HAS_XXX_TYPE_DEF(NAME, TYPE) \
	template<typename T, typename = typename T::TYPE> \
	std::true_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TYPE), NAME), __LINE__)(int); \
	template<typename T> \
	std::false_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_type_, TYPE), NAME), __LINE__)(long); \
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
	std::true_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_value_, VALUE), NAME), __LINE__)(int); \
	template<typename T> \
	std::false_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_value_, VALUE), NAME), __LINE__)(long); \
	template<typename T, typename Base_ = decltype(SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_value_, VALUE), NAME), __LINE__)<T>(0))> \
	struct NAME \
		: public Base_ \
	{}
#else
#define SPROUT_HAS_XXX_VALUE_DEF(NAME, VALUE) \
	template<typename T, decltype(&T::VALUE) = &T::VALUE> \
	std::true_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_value_, VALUE), NAME), __LINE__)(int); \
	template<typename T> \
	std::false_type SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_value_, VALUE), NAME), __LINE__)(long); \
	template<typename T> \
	struct NAME \
		: public decltype(SPROUT_PP_CAT(SPROUT_PP_CAT(SPROUT_PP_CAT(sprout_has_xxx_impl_check_value_, VALUE), NAME), __LINE__)<T>(0)) \
	{}
#endif
#define SPROUT_HAS_XXX_VALUE_DEF_LAZY(VALUE) \
	SPROUT_HAS_XXX_VALUE_DEF(SPROUT_PP_CAT(has_, VALUE), VALUE)

#endif	// #ifndef SPROUT_TYPE_TRAITS_HAS_XXX_HPP
