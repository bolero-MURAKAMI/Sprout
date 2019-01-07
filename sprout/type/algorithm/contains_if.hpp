/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_CONTAINTS_IF_HPP
#define SPROUT_TYPE_ALGORITHM_CONTAINTS_IF_HPP

#include <sprout/config.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/algorithm/any_of.hpp>

namespace sprout {
	namespace types {
		//
		// contains_if
		//
		template<typename Tuple, typename Predicate>
		struct contains_if
			: public sprout::types::any_of<Tuple, Predicate>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename Predicate>
		using contains_if_t = typename sprout::types::contains_if<Tuple, Predicate>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename Tuple, typename Predicate>
		SPROUT_STATIC_CONSTEXPR bool contains_if_v = sprout::types::contains_if<Tuple, Predicate>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_CONTAINTS_IF_HPP
