#ifndef SPROUT_RANGE_LVALUE_RANGE_HPP
#define SPROUT_RANGE_LVALUE_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/lvalue_iterator.hpp>

namespace sprout {
	namespace range {
		//
		// lvalue_range
		//
		template<typename Range>
		struct lvalue_range {
		public:
			typedef sprout::range::range_container<typename sprout::range::lvalue_iterator<Range>::type> type;
		};
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_LVALUE_RANGE_HPP
