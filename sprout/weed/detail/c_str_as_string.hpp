#ifndef SPROUT_WEED_DETAIL_C_STR_AS_STRING_HPP
#define SPROUT_WEED_DETAIL_C_STR_AS_STRING_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			template<typename T>
			struct c_str_as_string;
			template<typename T, std::size_t N>
			struct c_str_as_string<T const[N]> {
			public:
				typedef sprout::basic_string<T, N - 1> type;
			};
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_C_STR_AS_STRING_HPP
