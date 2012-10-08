#ifndef SPROUT_UTILITY_PAIR_MAKE_PAIR_HPP
#define SPROUT_UTILITY_PAIR_MAKE_PAIR_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/functional/ref.hpp>

namespace sprout {
	//
	// make_pair
	//
	template<typename T1, typename T2>
	inline SPROUT_CONSTEXPR sprout::pair<
		typename sprout::strip_reference<typename std::decay<T1>::type>::type,
		typename sprout::strip_reference<typename std::decay<T2>::type>::type
	>
	make_pair(T1&& x, T2&& y) {
		return sprout::pair<
			typename sprout::strip_reference<typename std::decay<T1>::type>::type,
			typename sprout::strip_reference<typename std::decay<T2>::type>::type
		>(
			sprout::forward<T1>(x),
			sprout::forward<T2>(y)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_MAKE_PAIR_HPP
