#ifndef SPROUT_WEED_DETAIL_UNCVREF_HPP
#define SPROUT_WEED_DETAIL_UNCVREF_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			template<typename T>
			struct uncvref
				: public std::conditional<
					std::is_array<T>::value
					|| std::is_array<typename std::remove_reference<T>::type>::value,
					typename std::remove_reference<T>::type,
					typename std::decay<T>::type
				>
			{};
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_UNCVREF_HPP
