#ifndef SPROUT_DETAIL_SIZEOF_HPP
#define SPROUT_DETAIL_SIZEOF_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename... Ts>
		struct sizeof_pack
			: public std::integral_constant<std::size_t, sizeof...(Ts)>
		{};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_SIZEOF_HPP
