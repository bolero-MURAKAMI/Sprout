#ifndef SPROUT_UTILITY_PAIR_HPP
#define SPROUT_UTILITY_PAIR_HPP

#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	//
	// pair
	//
	template <typename T1, typename T2>
	struct pair {
	public:
		typedef T1 first_type;
		typedef T2 second_type;
	public:
		T1 first;
		T2 second;
	public:
		SPROUT_CONSTEXPR pair(pair const&) = default;
		SPROUT_CONSTEXPR pair()
			: first()
			, second()
		{}
		SPROUT_CONSTEXPR pair(T1 const& x, T2 const& y)
			: first(x)
			, second(y)
		{}
		template<typename U, typename V>
		SPROUT_CONSTEXPR pair(sprout::pair<U, V> const& p)
			: first(p.first)
			, second(p.second)
		{}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_HPP
