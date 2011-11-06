#ifndef SPROUT_TYPE_ITERATOR_NEXT_HPP
#define SPROUT_TYPE_ITERATOR_NEXT_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// next
		//
		template<typename Iterator>
		struct next {
		public:
			typedef typename Iterator::next type;
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_NEXT_HPP
