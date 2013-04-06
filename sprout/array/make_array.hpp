#ifndef SPROUT_ARRAY_MAKE_ARRAY_HPP
#define SPROUT_ARRAY_MAKE_ARRAY_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/array/array.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/common_decay.hpp>

namespace sprout {
	//
	// make_array
	//
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<T, sizeof...(Types)>
	make_array(Types&&... args) {
		return sprout::array<T, sizeof...(Types)>{{sprout::forward<Types>(args)...}};
	}

	//
	// make_common_array
	//
	template<typename... Types>
	inline SPROUT_CONSTEXPR sprout::array<
		typename sprout::common_decay<Types&&...>::type,
		sizeof...(Types)
	>
	make_common_array(Types&&... args) {
		typedef sprout::array<
			typename sprout::common_decay<Types&&...>::type,
			sizeof...(Types)
		> type;
		return type{{sprout::forward<Types>(args)...}};
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ARRAY_MAKE_ARRAY_HPP
