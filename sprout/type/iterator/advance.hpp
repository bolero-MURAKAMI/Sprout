/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ITERATOR_ADVANCE_HPP
#define SPROUT_TYPE_ITERATOR_ADVANCE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>

namespace sprout {
	namespace types {
		//
		// advance
		//
		template<typename Iterator, std::ptrdiff_t Disatnce, typename Enable = void>
		struct advance
			: public Iterator::template advance<Disatnce>
		{};

		template<typename Iterator, std::ptrdiff_t Disatnce>
		struct advance<Iterator const, Disatnce>
			: public sprout::types::advance<Iterator, Disatnce>
		{};
		template<typename Iterator, std::ptrdiff_t Disatnce>
		struct advance<Iterator volatile, Disatnce>
			: public sprout::types::advance<Iterator, Disatnce>
		{};
		template<typename Iterator, std::ptrdiff_t Disatnce>
		struct advance<Iterator const volatile, Disatnce>
			: public sprout::types::advance<Iterator, Disatnce>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Iterator, std::ptrdiff_t Disatnce>
		using advance_t = typename sprout::types::advance<Iterator, Disatnce>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_ADVANCE_HPP
