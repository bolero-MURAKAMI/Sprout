#ifndef SPROUT_ARRAY_MAKE_ARRAY_HPP
#define SPROUT_ARRAY_MAKE_ARRAY_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/array/array.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// make_array
	//
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<T, sizeof...(Types)> make_array(Types&&... args) {
		return sprout::array<T, sizeof...(Types)>{{sprout::forward<Types>(args)...}};
	}

	//
	// make_common_array
	//
	template<typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<
		typename std::decay<typename std::common_type<typename std::decay<Types>::type...>::type>::type,
		sizeof...(Types)
	> make_common_array(Types&&... args) {
		return sprout::array<
			typename std::decay<typename std::common_type<typename std::decay<Types>::type...>::type>::type,
			sizeof...(Types)
		>{{sprout::forward<Types>(args)...}};
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ARRAY_MAKE_ARRAY_HPP
