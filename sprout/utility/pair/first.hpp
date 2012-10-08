#ifndef SPROUT_UTILITY_PAIR_FIRST_HPP
#define SPROUT_UTILITY_PAIR_FIRST_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// first
	//
	template<typename T>
	inline SPROUT_CONSTEXPR auto
	first(T&& t)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::get<0>(sprout::forward<T>(t))))
	-> decltype(sprout::tuples::get<0>(sprout::forward<T>(t)))
	{
		return sprout::tuples::get<0>(sprout::forward<T>(t));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_FIRST_HPP
