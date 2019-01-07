/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_DETAIL_HAS_BINARY_OP_HPP
#define SPROUT_TYPE_TRAITS_DETAIL_HAS_BINARY_OP_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/dont_care.hpp>
#include <sprout/preprocessor/cat.hpp>

#define SPROUT_DETAIL_HAS_BINARY_OP_INFIX_EXPR(OP, LHS, RHS) \
	LHS OP RHS

#define SPROUT_DETAIL_HAS_BINARY_OP_DECL(OP_NAME, OP, RHS_DEFAULT) \
	SPROUT_DETAIL_HAS_BINARY_OP_DECL_(OP_NAME, OP, RHS_DEFAULT, SPROUT_DETAIL_HAS_BINARY_OP_INFIX_EXPR)

#define SPROUT_DETAIL_HAS_BINARY_OP_DECL_(OP_NAME, OP, RHS_DEFAULT, EXPR) \
	template<typename T1, typename T2, typename R> \
	struct SPROUT_PP_CAT(sprout_detail_has_, SPROUT_PP_CAT(OP_NAME, _test)) { \
	public: \
		template< \
			typename U1 = T1, typename U2 = T2, \
			typename Result = sprout::bool_constant<std::is_convertible<typename sprout::identity<decltype(EXPR(OP, std::declval<U1>(), std::declval<U2>()))>::type, R>::value> \
		> \
		static Result test(int); \
		static sprout::false_type test(...); \
	}; \
	template<typename T1, typename T2> \
	struct SPROUT_PP_CAT(sprout_detail_has_, SPROUT_PP_CAT(OP_NAME, _test))<T1, T2, sprout::dont_care> { \
	public: \
		template< \
			typename U1 = T1, typename U2 = T2, \
			typename = typename sprout::identity<decltype(EXPR(OP, std::declval<U1>(), std::declval<U2>()))>::type \
		> \
		static sprout::true_type test(int); \
		static sprout::false_type test(...); \
	}; \
	SPROUT_DETAIL_HAS_BINARY_OP_DECL_IMPL(OP_NAME); \
	template<typename T, typename U RHS_DEFAULT, typename R = sprout::dont_care> \
	struct SPROUT_PP_CAT(has_, OP_NAME) \
		: public SPROUT_PP_CAT(sprout_detail_has_, OP_NAME)<T, U, R> \
	{}

#if defined(_MSC_VER) && (_MSC_VER > 1900)
#	define SPROUT_DETAIL_HAS_BINARY_OP_DECL_IMPL(OP_NAME) \
		template< \
			typename T, typename U, typename R, \
			typename Base_ = typename sprout::identity<decltype(SPROUT_PP_CAT(sprout_detail_has_, SPROUT_PP_CAT(OP_NAME, _test))<T, U, R>::test(0))>::type \
		> \
		struct SPROUT_PP_CAT(sprout_detail_has_, OP_NAME) \
			: public Base_ \
		{}
#else
#	define SPROUT_DETAIL_HAS_BINARY_OP_DECL_IMPL(OP_NAME) \
		template<typename T, typename U, typename R> \
		struct SPROUT_PP_CAT(sprout_detail_has_, OP_NAME) \
			: public sprout::identity<decltype(SPROUT_PP_CAT(sprout_detail_has_, SPROUT_PP_CAT(OP_NAME, _test))<T, U, R>::test(0))>::type \
		{}
#endif

#endif	// #ifndef SPROUT_TYPE_TRAITS_DETAIL_HAS_BINARY_OP_HPP
