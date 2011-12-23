#ifndef TESTSPR_SPROUT_HPP
#define TESTSPR_SPROUT_HPP

#include <testspr/sprout/array.hpp>
#include <testspr/sprout/string.hpp>
#include <testspr/sprout/algorithm.hpp>
#include <testspr/sprout/random.hpp>

namespace testspr {
	static void sprout_test() {
		testspr::array_test();
		testspr::string_test();
		testspr::algorithm_test();
		testspr::random_test();
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_HPP
