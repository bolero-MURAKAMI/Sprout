#ifndef SPROUT_TYPE_ITERATOR_DEREF_HPP
#define SPROUT_TYPE_ITERATOR_DEREF_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// deref
		//
		template<typename Iterator>
		struct deref {
		public:
			typedef typename Iterator::type type;
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_DEREF_HPP
