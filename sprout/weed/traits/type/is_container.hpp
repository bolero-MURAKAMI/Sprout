#ifndef SPROUT_WEED_TRAITS_TYPE_IS_CONTAINER_HPP
#define SPROUT_WEED_TRAITS_TYPE_IS_CONTAINER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/array.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_container
			//
			template<typename T>
			struct is_container
				: public std::false_type
			{};
			template<typename T>
			struct is_container<T const>
				: public sprout::weed::traits::is_container<T>
			{};
			template<typename T, std::size_t N>
			struct is_container<sprout::array<T, N> >
				: public std::true_type
			{};
			template<typename T, std::size_t N, typename Traits>
			struct is_container<sprout::basic_string<T, N, Traits> >
				: public std::true_type
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_TYPE_IS_CONTAINER_HPP
