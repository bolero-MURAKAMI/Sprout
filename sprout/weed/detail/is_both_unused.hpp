#ifndef SPROUT_WEED_DETAIL_IS_BOTH_UNUSED_HPP
#define SPROUT_WEED_DETAIL_IS_BOTH_UNUSED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/traits/type/is_unused.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			template<typename T, typename U, typename = void>
			struct is_both_unused
				: public std::false_type
			{};
			template<typename T, typename U>
			struct is_both_unused<
				T,
				U,
				typename std::enable_if<
					sprout::weed::traits::is_unused<T>::value
					&& sprout::weed::traits::is_unused<U>::value
				>::type
			>
				: public std::true_type
			{};
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_IS_BOTH_UNUSED_HPP
