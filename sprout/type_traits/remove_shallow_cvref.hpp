/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_CVREF_HPP
#define SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_CVREF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/remove_shallow_cv.hpp>

namespace sprout {
	//
	// remove_shallow_cvref
	//
	template<typename T>
	struct remove_shallow_cvref
		: public sprout::remove_shallow_cv<
			typename std::remove_reference<T>::type
		>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using remove_shallow_cvref_t = typename sprout::remove_shallow_cvref<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_CVREF_HPP
