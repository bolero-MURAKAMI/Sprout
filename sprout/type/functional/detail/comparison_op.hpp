/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_FUNCTIONAL_DETAIL_COMPARISON_OP_HPP
#define SPROUT_TYPE_FUNCTIONAL_DETAIL_COMPARISON_OP_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type/quote.hpp>
#include <sprout/preprocessor/cat.hpp>

#define SPROUT_TYPES_DETAIL_FUNCTIONAL_COMPARISON_OP_DECL(NAME, OP) \
namespace sprout { \
	namespace types { \
		template<typename T, typename U> \
		struct NAME \
			: public sprout::bool_constant<((T::value) OP (U::value))> \
		{}; \
		typedef sprout::types::quote<sprout::types::NAME> SPROUT_PP_CAT(NAME, _); \
		SPROUT_TYPES_DETAIL_FUNCTIONAL_COMPARISON_OP_VT_DECL(NAME) \
	} \
}

#if SPROUT_USE_VARIABLE_TEMPLATES
#	define SPROUT_TYPES_DETAIL_FUNCTIONAL_COMPARISON_OP_VT_DECL(NAME) \
		template<typename T, typename U> \
		SPROUT_STATIC_CONSTEXPR bool SPROUT_PP_CAT(NAME, _v) = sprout::types::NAME<T, U>::value;
#else	// #if SPROUT_USE_VARIABLE_TEMPLATES
#	define SPROUT_TYPES_DETAIL_FUNCTIONAL_COMPARISON_OP_VT_DECL(NAME)
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES

#endif	// #ifndef SPROUT_TYPE_FUNCTIONAL_DETAIL_COMPARISON_OP_HPP
