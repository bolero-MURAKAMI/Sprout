#ifndef SPROUT_FUNCTIONAL_PLUS_HPP
#define SPROUT_FUNCTIONAL_PLUS_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 20.8.4 Arithmetic operations
	template<typename T = void>
	struct plus {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef T result_type;
	public:
		SPROUT_CONSTEXPR T operator()(T const& x, T const& y) const {
			return x + y;
		}
	};

	template<>
	struct plus<void> {
	public:
		template<typename T, typename U>
		SPROUT_CONSTEXPR decltype(std::declval<T>() + std::declval<U>())
		operator()(T&& x, U&& y)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<T>() + std::declval<U>()))
		{
			return sprout::forward<T>(x) + sprout::forward<U>(y);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_PLUS_HPP
