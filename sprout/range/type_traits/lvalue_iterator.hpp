/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_TYPE_TRAITS_LVALUE_ITERATOR_HPP
#define SPROUT_RANGE_TYPE_TRAITS_LVALUE_ITERATOR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>

namespace sprout {
	namespace range {
		//
		// lvalue_iterator
		//
		template<typename Range>
		struct lvalue_iterator {
		public:
			typedef typename sprout::container_traits<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>::iterator type;
		};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Range>
		using lvalue_iterator_t = typename sprout::range::lvalue_iterator<Range>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_TYPE_TRAITS_LVALUE_ITERATOR_HPP
