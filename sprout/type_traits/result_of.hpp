/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_RESULT_OF_HPP
#define SPROUT_TYPE_TRAITS_RESULT_OF_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/detail/invoke.hpp>

namespace sprout {
	//
	// result_of
	//
	template<typename>
	struct result_of;
	template<typename F, typename... Args>
	struct result_of<F(Args...)>
		: public sprout::detail::invoke_result<void, F, Args...>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using result_of_t = typename sprout::result_of<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_RESULT_OF_HPP
