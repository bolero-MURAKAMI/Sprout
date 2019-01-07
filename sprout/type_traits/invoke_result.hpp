/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_INVOKE_RESULT_HPP
#define SPROUT_TYPE_TRAITS_INVOKE_RESULT_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/detail/invoke.hpp>

namespace sprout {
	//
	// invoke_result
	//
	template<typename F, typename... Args>
	struct invoke_result
		: public sprout::detail::invoke_result<void, F, Args...>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename F, typename... Args>
	using invoke_result_t = typename sprout::invoke_result<F, Args...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_INVOKE_RESULT_HPP
