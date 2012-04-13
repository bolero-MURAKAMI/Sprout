#ifndef SPROUT_WEED_TRAITS_EXPR_IS_EXPR_HPP
#define SPROUT_WEED_TRAITS_EXPR_IS_EXPR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/expr/expr.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_expr
			//
			template<typename T>
			struct is_expr
				: public std::false_type
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
				: public std::true_type
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_EXPR_IS_EXPR_HPP
