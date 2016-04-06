/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_DETAIL_HAS_POST_UNARY_OP_HPP
#define SPROUT_TYPE_TRAITS_DETAIL_HAS_POST_UNARY_OP_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/dont_care.hpp>
#include <sprout/preprocessor/cat.hpp>

#define SPROUT_DETAIL_HAS_POST_UNARY_OP_DECL(OP_NAME, OP) \
	template<typename T, typename R> \
	struct SPROUT_PP_CAT(sprout_detail_has_, SPROUT_PP_CAT(OP_NAME, _test)) { \
	public: \
		template< \
			typename U = T, \
			typename Result = sprout::bool_constant<std::is_convertible<typename sprout::identity<decltype(std::declval<U>() OP)>::type, R>::value> \
		> \
		static Result test(int); \
		static sprout::false_type test(...); \
	}; \
	template<typename T> \
	struct SPROUT_PP_CAT(sprout_detail_has_, SPROUT_PP_CAT(OP_NAME, _test))<T, sprout::dont_care> { \
	public: \
		template< \
			typename U = T, \
			typename = typename sprout::identity<decltype(std::declval<U>() OP)>::type \
		> \
		static sprout::true_type test(int); \
		static sprout::false_type test(...); \
	}; \
	SPROUT_DETAIL_HAS_POST_UNARY_OP_DECL_IMPL(OP_NAME); \
	template<typename T, typename R = sprout::dont_care> \
	struct SPROUT_PP_CAT(has_, OP_NAME) \
		: public SPROUT_PP_CAT(sprout_detail_has_, OP_NAME)<T, R> \
	{}

#if defined(_MSC_VER) && (_MSC_VER > 1900)
#	define SPROUT_DETAIL_HAS_POST_UNARY_OP_DECL_IMPL(OP_NAME) \
		template< \
			typename T, typename R, \
			typename Base_ = typename sprout::identity<decltype(SPROUT_PP_CAT(sprout_detail_has_, SPROUT_PP_CAT(OP_NAME, _test))<T, R>::test(0))>::type \
		> \
		struct SPROUT_PP_CAT(sprout_detail_has_, OP_NAME) \
			: public Base_ \
		{}
#else
#	define SPROUT_DETAIL_HAS_POST_UNARY_OP_DECL_IMPL(OP_NAME) \
		template<typename T, typename R> \
		struct SPROUT_PP_CAT(sprout_detail_has_, OP_NAME) \
			: public sprout::identity<decltype(SPROUT_PP_CAT(sprout_detail_has_, SPROUT_PP_CAT(OP_NAME, _test))<T, R>::test(0))>::type \
		{}
#endif

#endif	// #ifndef SPROUT_TYPE_TRAITS_DETAIL_HAS_POST_UNARY_OP_HPP
