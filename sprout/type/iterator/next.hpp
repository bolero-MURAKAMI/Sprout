/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ITERATOR_NEXT_HPP
#define SPROUT_TYPE_ITERATOR_NEXT_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// next
		//
		template<typename Iterator, typename Enable = void>
		struct next {
		public:
			typedef typename Iterator::next type;
		};

		template<typename Iterator>
		struct next<Iterator const>
			: public sprout::types::next<Iterator>
		{};
		template<typename Iterator>
		struct next<Iterator volatile>
			: public sprout::types::next<Iterator>
		{};
		template<typename Iterator>
		struct next<Iterator const volatile>
			: public sprout::types::next<Iterator>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Iterator>
		using next_t = typename sprout::types::next<Iterator>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_NEXT_HPP
