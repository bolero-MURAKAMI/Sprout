/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
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
