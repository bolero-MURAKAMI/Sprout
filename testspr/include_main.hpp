#ifndef TESTSPR_INCLUDE_MAIN_HPP
#define TESTSPR_INCLUDE_MAIN_HPP

#ifndef TESTSPR_CPP_INCLUDE

#ifndef TESTSPR_TEST_FUNCTION
#	error undefined TESTSPR_TEST_FUNCTION
#endif

#include <iostream>
#include <sprout/preprocessor/stringize.hpp>

int main() {
	std::cout << "testspr exec: " << SPROUT_PP_STRINGIZE(TESTSPR_TEST_FUNCTION) << std::endl;
	TESTSPR_TEST_FUNCTION();
	std::cout << "testspr succeeded." << std::endl;
}

#endif

#endif	// #ifndef TESTSPR_INCLUDE_MAIN_HPP
