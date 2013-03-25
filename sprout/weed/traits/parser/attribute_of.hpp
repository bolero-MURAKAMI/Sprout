#ifndef SPROUT_WEED_TRAITS_PARSER_ATTRIBUTE_OF_HPP
#define SPROUT_WEED_TRAITS_PARSER_ATTRIBUTE_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/traits/expr/is_expr.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/expr/expr.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/traits/type/is_char_type.hpp>
#include <sprout/weed/traits/type/is_c_str.hpp>
#include <sprout/weed/traits/type/is_string.hpp>
#include <sprout/weed/traits/expr/is_expr.hpp>
#include <sprout/weed/traits/expr/terminal_of.hpp>
#include <sprout/weed/traits/parser/is_parser.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// attribute_of
			//
			template<typename T, typename Iterator, typename Context, typename = void>
			struct attribute_of;
			template<typename T, typename Iterator, typename Context>
			struct attribute_of<T const, Iterator, Context>
				: public sprout::weed::traits::attribute_of<T, Iterator, Context>
			{};
			template<typename T, typename Iterator, typename Context>
			struct attribute_of<
				T,
				Iterator,
				Context,
				typename std::enable_if<
					sprout::weed::traits::is_parser<T>::value
					&& !sprout::weed::traits::is_expr<T>::value
					&& !sprout::weed::traits::is_char_type<T>::value
					&& !sprout::weed::traits::is_c_str<T>::value
					&& !sprout::weed::traits::is_string<T>::value
				>::type
			>
				: public T::template attribute<Context, Iterator>
			{};
			template<typename T, typename Iterator, typename Context>
			struct attribute_of<
				T,
				Iterator,
				Context,
				typename std::enable_if<
					sprout::weed::traits::is_expr<T>::value
				>::type
			>
				: public sprout::identity<typename Context::template eval<T>::attribute_type>
			{};
			template<typename T, typename Iterator, typename Context>
			struct attribute_of<
				T,
				Iterator,
				Context,
				typename std::enable_if<
					sprout::weed::traits::is_char_type<T>::value
					|| sprout::weed::traits::is_c_str<T>::value
					|| sprout::weed::traits::is_string<T>::value
				>::type
			>
				: public sprout::weed::traits::attribute_of<
					typename sprout::weed::traits::terminal_of<T>::type,
					Iterator,
					Context
				>
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_PARSER_ATTRIBUTE_OF_HPP
