/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_USE_DEFAULT_HPP
#define SPROUT_UTILITY_USE_DEFAULT_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// use_default
	//
	struct use_default;

	//
	// is_use_default
	//
	template<typename T>
	struct is_use_default
		: public sprout::is_same<T, sprout::use_default>
	{};

	//
	// select_default
	//
	template<typename T, typename Default>
	struct select_default
		: public std::conditional<sprout::is_use_default<T>::value, Default, T>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_USE_DEFAULT_HPP
