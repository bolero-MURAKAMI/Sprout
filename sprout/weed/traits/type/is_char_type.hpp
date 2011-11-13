#ifndef SPROUT_WEED_TRAITS_TYPE_IS_CHAR_TYPE_HPP
#define SPROUT_WEED_TRAITS_TYPE_IS_CHAR_TYPE_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_char_type
			//
			template<typename T>
			struct is_char_type
				: public std::false_type
			{};
			template<typename T>
			struct is_char_type<T const>
				: public sprout::weed::traits::is_char_type<T>
			{};
			template<>
			struct is_char_type<char>
				: public std::true_type
			{};
			template<>
			struct is_char_type<wchar_t>
				: public std::true_type
			{};
			template<>
			struct is_char_type<char16_t>
				: public std::true_type
			{};
			template<>
			struct is_char_type<char32_t>
				: public std::true_type
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_TYPE_IS_CHAR_TYPE_HPP
