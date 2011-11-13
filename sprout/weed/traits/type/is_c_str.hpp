#ifndef SPROUT_WEED_TRAITS_TYPE_IS_C_STR_HPP
#define SPROUT_WEED_TRAITS_TYPE_IS_C_STR_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_c_str
			//
			template<typename T>
			struct is_c_str
				: public std::false_type
			{};
			template<typename T>
			struct is_c_str<T const>
				: public sprout::weed::traits::is_c_str<T>
			{};
			template<std::size_t N>
			struct is_c_str<char const[N]>
				: public std::true_type
			{};
			template<std::size_t N>
			struct is_c_str<wchar_t const[N]>
				: public std::true_type
			{};
			template<std::size_t N>
			struct is_c_str<char16_t const[N]>
				: public std::true_type
			{};
			template<std::size_t N>
			struct is_c_str<char32_t const[N]>
				: public std::true_type
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_TYPE_IS_C_STR_HPP
