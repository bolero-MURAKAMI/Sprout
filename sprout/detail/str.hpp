#ifndef SPROUT_DETAIL_STR_HPP
#define SPROUT_DETAIL_STR_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR InputIterator
		str_find_check(InputIterator found) {
			return !*found ? InputIterator()
				: found
				;
		}

		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR InputIterator
		str_find_check(InputIterator found, T const& value) {
			return !(*found == value) && !*found ? InputIterator()
				: found
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif // #ifndef SPROUT_DETAIL_STR_HPP
