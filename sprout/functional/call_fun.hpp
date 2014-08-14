/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_CALL_FUN_HPP
#define SPROUT_FUNCTIONAL_CALL_FUN_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// call_fun
	//
	template<typename T = void>
	struct call_fun;
	template<>
	struct call_fun<void> {
	public:
		typedef void is_transparent;
	public:
		template<typename F, typename... As>
		SPROUT_CONSTEXPR decltype(std::declval<F>()(std::declval<As>()...))
		operator()(F&& f, As&&... as)
		const SPROUT_NOEXCEPT_IF_EXPR(std::declval<F>()(std::declval<As>()...))
		{
			return SPROUT_FORWARD(F, f)(SPROUT_FORWARD(As, as)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_CALL_FUN_HPP
