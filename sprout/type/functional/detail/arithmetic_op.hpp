/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_FUNCTIONAL_DETAIL_ARITHMETIC_OP_HPP
#define SPROUT_TYPE_FUNCTIONAL_DETAIL_ARITHMETIC_OP_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/arithmetic_promote.hpp>
#include <sprout/preprocessor/cat.hpp>

#define SPROUT_TYPES_DETAIL_FUNCTIONAL_ARITHMETIC_BINARY_OP_DECL(NAME, OP) \
namespace sprout { \
	namespace types { \
		template<typename T, typename U, typename Result = void> \
		struct NAME \
			: public sprout::integral_constant<Result, (T::value OP U::value)> \
		{}; \
		template<typename T, typename U> \
		struct NAME<T, U, void> \
			: public sprout::integral_constant< \
				typename sprout::arithmetic_promote<typename T::value_type, typename U::value_type>::type, \
				(T::value OP U::value) \
			> \
		{}; \
		template<typename Result = void> \
		struct SPROUT_PP_CAT(NAME, _mf) { \
		public: \
			template<typename T, typename U> \
			struct apply \
				: public sprout::types::NAME<T, U, Result> \
			{}; \
		}; \
		typedef sprout::types::SPROUT_PP_CAT(NAME, _mf)<> SPROUT_PP_CAT(NAME, _); \
		SPROUT_TYPES_DETAIL_FUNCTIONAL_ARITHMETIC_BINARY_OP_VT_DECL(NAME) \
	} \
}
#if SPROUT_USE_VARIABLE_TEMPLATES
#	define SPROUT_TYPES_DETAIL_FUNCTIONAL_ARITHMETIC_BINARY_OP_VT_DECL(NAME) \
		template<typename T, typename U, typename Result = void> \
		SPROUT_STATIC_CONSTEXPR typename sprout::types::NAME<T, U, Result>::value_type SPROUT_PP_CAT(NAME, _v) = sprout::types::NAME<T, U, Result>::value;
#else	// #if SPROUT_USE_VARIABLE_TEMPLATES
#	define SPROUT_TYPES_DETAIL_FUNCTIONAL_ARITHMETIC_BINARY_OP_VT_DECL(NAME)
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES

#define SPROUT_TYPES_DETAIL_FUNCTIONAL_ARITHMETIC_UNARY_OP_DECL(NAME, OP) \
namespace sprout { \
	namespace types { \
		template<typename T, typename Result = void> \
		struct NAME \
			: public sprout::integral_constant<Result, (OP T::value)> \
		{}; \
		template<typename T> \
		struct NAME<T, void> \
			: public sprout::integral_constant< \
				typename sprout::arithmetic_promote<typename T::value_type>::type, \
				(OP T::value) \
			> \
		{}; \
		template<typename Result = void> \
		struct SPROUT_PP_CAT(NAME, _mf) { \
		public: \
			template<typename T> \
			struct apply \
				: public sprout::types::NAME<T, Result> \
			{}; \
		}; \
		typedef sprout::types::SPROUT_PP_CAT(NAME, _mf)<> SPROUT_PP_CAT(NAME, _); \
		SPROUT_TYPES_DETAIL_FUNCTIONAL_ARITHMETIC_UNARY_OP_VT_DECL(NAME) \
	} \
}
#if SPROUT_USE_VARIABLE_TEMPLATES
#	define SPROUT_TYPES_DETAIL_FUNCTIONAL_ARITHMETIC_UNARY_OP_VT_DECL(NAME) \
		template<typename T, typename Result = void> \
		SPROUT_STATIC_CONSTEXPR typename sprout::types::NAME<T, Result>::value_type SPROUT_PP_CAT(NAME, _v) = sprout::types::NAME<T, Result>::value;
#else	// #if SPROUT_USE_VARIABLE_TEMPLATES
#	define SPROUT_TYPES_DETAIL_FUNCTIONAL_ARITHMETIC_UNARY_OP_VT_DECL(NAME)
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES

#endif	// #ifndef SPROUT_TYPE_FUNCTIONAL_DETAIL_ARITHMETIC_OP_HPP
