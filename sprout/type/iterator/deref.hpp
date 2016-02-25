/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ITERATOR_DEREF_HPP
#define SPROUT_TYPE_ITERATOR_DEREF_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// deref
		//
		template<typename Iterator>
		struct deref
			: public Iterator
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Iterator>
		using deref_t = typename sprout::types::deref<Iterator>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_DEREF_HPP
