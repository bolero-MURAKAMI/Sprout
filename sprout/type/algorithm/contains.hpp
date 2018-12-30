/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_CONTAINTS_HPP
#define SPROUT_TYPE_ALGORITHM_CONTAINTS_HPP

#include <sprout/config.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/algorithm/any_of_same.hpp>

namespace sprout {
	namespace types {
		//
		// contains
		//
		template<typename Tuple, typename T>
		struct contains
			: public sprout::types::any_of_same<Tuple, T>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename T>
		using contains_t = typename sprout::types::contains<Tuple, T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename Tuple, typename T>
		SPROUT_STATIC_CONSTEXPR bool contains_v = sprout::types::contains<Tuple, T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_CONTAINTS_HPP
