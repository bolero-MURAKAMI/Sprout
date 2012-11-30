#ifndef SPROUT_WEED_TRAITS_PARSER_IS_PARSER_HPP
#define SPROUT_WEED_TRAITS_PARSER_IS_PARSER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/parser/parser_base.hpp>
#include <sprout/weed/traits/type/is_char_type.hpp>
#include <sprout/weed/traits/type/is_c_str.hpp>
#include <sprout/weed/traits/expr/is_expr.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_parser
			//
			template<typename T, typename = void>
			struct is_parser;
			template<typename T>
			struct is_parser<
				T,
				typename std::enable_if<
					std::is_base_of<sprout::weed::parser_base, T>::value
					&& !std::is_const<T>::value
				>::type
			>
				: public std::true_type
			{};
			template<typename T>
			struct is_parser<
				T,
				typename std::enable_if<
					sprout::weed::traits::is_expr<T>::value
					&& !std::is_const<T>::value
				>::type
			>
				: public std::true_type
			{};
			template<typename T>
			struct is_parser<
				T,
				typename std::enable_if<
					sprout::weed::traits::is_char_type<T>::value
					&& !std::is_const<T>::value
				>::type
			>
				: public std::true_type
			{};
			template<typename T>
			struct is_parser<
				T,
				typename std::enable_if<
					sprout::weed::traits::is_c_str<T>::value
				>::type
			>
				: public std::true_type
			{};
			template<typename T>
			struct is_parser<
				T,
				typename std::enable_if<
					std::is_const<T>::value
					&& !std::is_array<T>::value
				>::type
			>
				: public sprout::weed::traits::is_parser<
					typename std::remove_const<T>::type
				>
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_PARSER_IS_PARSER_HPP
