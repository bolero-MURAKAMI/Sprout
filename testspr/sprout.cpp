#ifndef TESTSPR_SPROUT_CPP
#define TESTSPR_SPROUT_CPP

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_CPP_INCLUDE_DISABLE_TESTSPR_SPROUT_HPP
#	define TESTSPR_CPP_INCLUDE
#endif

#include "../libs/array/test/array.cpp"
#include "../libs/string/test/string.cpp"
#include "../libs/bitset/test/bitset.cpp"
#include "../libs/tuple/test/tuple.cpp"
#include "../libs/optional/test/optional.cpp"
#include "../libs/variant/test/variant.cpp"
#include "../libs/algorithm/test/algorithm.cpp"
#include "../libs/random/test/random.cpp"
#include "../libs/cstring/test/cstring.cpp"

#ifdef TESTSPR_CPP_INCLUDE_DISABLE_TESTSPR_SPROUT_HPP
#	undef TESTSPR_CPP_INCLUDE
#endif

namespace testspr {
	static void sprout_test() {
		testspr::array_test();
		testspr::string_test();
		testspr::bitset_test();
		testspr::tuple_test();
		testspr::optional_test();
		testspr::variant_test();
		testspr::algorithm_test();
		testspr::random_test();
		testspr::cstring_test();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::sprout_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef TESTSPR_SPROUT_CPP
