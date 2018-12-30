/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_TRAITS_EXPR_IS_EXPR_HPP
#define SPROUT_WEED_TRAITS_EXPR_IS_EXPR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/weed/expr/expr_fwd.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_expr
			//
			template<typename T>
			struct is_expr
				: public sprout::false_type
			{};
			template<typename T>
			struct is_expr<T const>
				: public sprout::weed::traits::is_expr<T>
			{};
			template<typename T>
			struct is_expr<T volatile>
				: public sprout::weed::traits::is_expr<T>
			{};
			template<typename T>
			struct is_expr<T const volatile>
				: public sprout::weed::traits::is_expr<T>
			{};
			template<typename Tag, typename... Args>
			struct is_expr<sprout::weed::expr<Tag, Args...> >
				: public sprout::true_type
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_EXPR_IS_EXPR_HPP
