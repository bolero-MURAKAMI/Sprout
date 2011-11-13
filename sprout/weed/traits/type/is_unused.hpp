#ifndef SPROUT_WEED_TRAITS_TYPE_IS_UNUSED_HPP
#define SPROUT_WEED_TRAITS_TYPE_IS_UNUSED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/unused.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_unused
			//
			template<typename T>
			struct is_unused
				: public std::is_same<T, sprout::weed::unused>
			{};
			template<typename T>
			struct is_unused<T const>
				: public sprout::weed::traits::is_unused<T>
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_TYPE_IS_UNUSED_HPP
