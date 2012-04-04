#ifndef SPROUT_RANGE_LVREF_ITERATOR_HPP
#define SPROUT_RANGE_LVREF_ITERATOR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/utility/operation_ext.hpp>

namespace sprout {
	namespace range {
		//
		// lvref_iterator
		//
		template<typename Range>
		struct lvref_iterator {
		public:
			typedef typename sprout::container_traits<
				typename std::remove_reference<typename sprout::lvref<Range>::type>::type
			>::iterator type;
		};
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_LVREF_ITERATOR_HPP
