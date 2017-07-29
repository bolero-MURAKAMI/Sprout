/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ITERATOR_PREV_HPP
#define SPROUT_TYPE_ITERATOR_PREV_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// prev
		//
		template<typename Iterator, typename Enable = void>
		struct prev {
		public:
			typedef typename Iterator::prev type;
		};

		template<typename Iterator>
		struct prev<Iterator const>
			: public sprout::types::prev<Iterator>
		{};
		template<typename Iterator>
		struct prev<Iterator volatile>
			: public sprout::types::prev<Iterator>
		{};
		template<typename Iterator>
		struct prev<Iterator const volatile>
			: public sprout::types::prev<Iterator>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Iterator>
		using prev_t = typename sprout::types::prev<Iterator>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_PREV_HPP
