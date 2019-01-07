/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_CONST_REFERENCE_HPP
#define SPROUT_TYPE_TRAITS_CONST_REFERENCE_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	//
	// const_reference
	//
	template<typename T>
	struct const_reference
		: public sprout::identity<decltype(sprout::as_const(std::declval<T&&>()))>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using const_reference_t = typename sprout::const_reference<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_CONST_REFERENCE_HPP
