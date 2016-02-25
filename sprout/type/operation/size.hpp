/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_SIZE_HPP
#define SPROUT_TYPE_OPERATION_SIZE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/tuple.hpp>

namespace sprout {
	namespace types {
		//
		// size
		//
		template<typename Tuple>
		struct size
			: public sprout::types::tuple_size<Tuple>
		{};

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename Tuple>
		SPROUT_STATIC_CONSTEXPR std::size_t size_v = sprout::types::size<Tuple>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_SIZE_HPP
