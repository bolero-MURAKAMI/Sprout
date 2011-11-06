#ifndef SPROUT_TYPE_ITERATOR_PREV_HPP
#define SPROUT_TYPE_ITERATOR_PREV_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// prev
		//
		template<typename Iterator>
		struct prev {
		public:
			typedef typename Iterator::prev type;
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_PREV_HPP
