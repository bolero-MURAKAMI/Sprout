#ifndef SPROUT_ITERATOR_DETAIL_ITERATOR_TO_POINTER_HPP
#define SPROUT_ITERATOR_DETAIL_ITERATOR_TO_POINTER_HPP

#include <iterator>
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
