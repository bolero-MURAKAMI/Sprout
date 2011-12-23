#ifndef TESTSPR_SPROUT_RANDOM_SHUFFLE_ORDER_HPP
#define TESTSPR_SPROUT_RANDOM_SHUFFLE_ORDER_HPP

#include <sprout/random/shuffle_order.hpp>
#include <testspr/sprout/random/engine_generic.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	void random_shuffle_order_test() {
		using namespace sprout;

		testspr::random_engine_test_generic<sprout::random::knuth_b>();
		testspr::random_engine_test_generic<sprout::random::kreutzer1986>();
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_RANDOM_SHUFFLE_ORDER_HPP
