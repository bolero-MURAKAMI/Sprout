#ifndef SPROUT_RANGE_LVREF_RANGE_HPP
#define SPROUT_RANGE_LVREF_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/lvref_iterator.hpp>

namespace sprout {
	namespace range {
		//
		// lvref_range
		//
		template<typename Range>
		struct lvref_range {
		public:
			typedef sprout::range::range_container<typename sprout::range::lvref_iterator<Range>::type> type;
		};
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_LVREF_RANGE_HPP
