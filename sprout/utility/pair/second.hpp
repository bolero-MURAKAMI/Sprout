#ifndef SPROUT_UTILITY_PAIR_SECOND_HPP
#define SPROUT_UTILITY_PAIR_SECOND_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/tuple.hpp>

namespace sprout {
	//
	// second
	//
	template<typename T>
	inline SPROUT_CONSTEXPR auto
	second(T&& t)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::get<1>(sprout::forward<T>(t))))
	-> decltype(sprout::tuples::get<1>(sprout::forward<T>(t)))
	{
		return sprout::tuples::get<1>(sprout::forward<T>(t));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_SECOND_HPP
