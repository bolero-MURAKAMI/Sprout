/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_DETAIL_ITERATOR_TO_POINTER_HPP
#define SPROUT_ITERATOR_DETAIL_ITERATOR_TO_POINTER_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename Derived, typename Pointer, bool ConvertibleToPointer = true>
		class iterator_to_pointer_base {};
		template<typename Derived, typename Pointer>
		class iterator_to_pointer_base<Derived, Pointer, true> {
		public:
			SPROUT_CONSTEXPR operator Pointer() const {
				return &*static_cast<Derived const&>(*this);
			}
		};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_DETAIL_ITERATOR_TO_POINTER_HPP
