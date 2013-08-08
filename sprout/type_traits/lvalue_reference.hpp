/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_LVALUE_REFERENCE_HPP
#define SPROUT_TYPE_TRAITS_LVALUE_REFERENCE_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/utility/as_lvalue.hpp>

namespace sprout {
	//
	// lvalue_reference
	//
	template<typename T>
	struct lvalue_reference
		: public sprout::identity<decltype(sprout::as_lvalue(std::declval<T&&>()))>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using lvalue_reference_t = typename sprout::lvalue_reference<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_LVALUE_REFERENCE_HPP
