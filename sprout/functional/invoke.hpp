/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_INVOKE_HPP
#define SPROUT_FUNCTIONAL_INVOKE_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/invoke_result.hpp>
#include <sprout/type_traits/is_nothrow_invocable.hpp>
#include <sprout/type_traits/detail/invoke.hpp>

namespace sprout {
	//
	// invoke
	//
	template<typename F, typename... Args>
	inline SPROUT_CONSTEXPR typename sprout::invoke_result<F, Args...>::type
	invoke(F&& f, Args&&... args) SPROUT_NOEXCEPT_IF((sprout::is_nothrow_invocable<F, Args...>::value)) {
		return sprout::detail::invoke(sprout::forward<F>(f), sprout::forward<Args>(args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_INVOKE_HPP
