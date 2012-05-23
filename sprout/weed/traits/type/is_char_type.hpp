#ifndef SPROUT_WEED_TRAITS_TYPE_IS_CHAR_TYPE_HPP
#define SPROUT_WEED_TRAITS_TYPE_IS_CHAR_TYPE_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/is_char_type.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_char_type
			//
			template<typename T>
			struct is_char_type
				: public sprout::is_char_type<T>
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_TYPE_IS_CHAR_TYPE_HPP
