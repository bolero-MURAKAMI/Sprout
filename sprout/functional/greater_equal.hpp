#ifndef SPROUT_FUNCTIONAL_GREATER_EQUAL_HPP
#define SPROUT_FUNCTIONAL_GREATER_EQUAL_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 20.8.5 Comparisons
	template<typename T = void>
	struct greater_equal {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& x, T const& y) const {
				return x >= y;
		}
	};

	template<>
	struct greater_equal<void> {
	public:
		template<typename T, typename U>
		SPROUT_CONSTEXPR decltype(std::declval<T>() >= std::declval<U>())
		operator()(T&& x, U&& y)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<T>() >= std::declval<U>()))
		{
			return sprout::forward<T>(x) >= sprout::forward<U>(y);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_GREATER_EQUAL_HPP
