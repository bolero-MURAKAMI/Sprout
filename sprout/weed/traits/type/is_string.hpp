#ifndef SPROUT_WEED_TRAITS_TYPE_IS_STRING_HPP
#define SPROUT_WEED_TRAITS_TYPE_IS_STRING_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_string
			//
			template<typename T>
			struct is_string
				: public std::false_type
			{};
			template<typename T>
			struct is_string<T const>
				: public sprout::weed::traits::is_string<T>
			{};
			template<typename T, std::size_t N, typename Traits>
			struct is_string<sprout::basic_string<T, N, Traits> >
				: public std::true_type
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_TYPE_IS_STRING_HPP
