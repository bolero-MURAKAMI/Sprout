#ifndef SPROUT_FUNCTIONAL_POSITE_HPP
#define SPROUT_FUNCTIONAL_POSITE_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 20.8.4 Arithmetic operations
	template<typename T = void>
	struct posite {
	public:
		typedef T argument_type;
		typedef T result_type;
	public:
		SPROUT_CONSTEXPR T operator()(T const& x) const {
				return +x;
		}
	};

	template<>
	struct posite<void> {
	public:
		template<typename T>
		SPROUT_CONSTEXPR decltype(+std::declval<T>())
		operator()(T&& x)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(+std::declval<T>()))
		{
			return +sprout::forward<T>(x);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POSITE_HPP
