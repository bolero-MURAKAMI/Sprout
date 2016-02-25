/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
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

#include <cstdlib>
#include <exception>
#include <iostream>
#include <sprout/preprocessor/stringize.hpp>
#include <testspr/assert.hpp>
#include <testspr/typeinfo.hpp>

int main() {
	std::cout << "testspr exec(" << SPROUT_PP_STRINGIZE(TESTSPR_TEST_FUNCTION) << "):" << std::endl;
	try {
		TESTSPR_TEST_FUNCTION();
	} catch (testspr::assertion_failed const& e) {
		std::cout
			<< "  testspr failed." << std::endl
			<< "  " << e.what() << std::endl
			;
		return EXIT_FAILURE;
	} catch (std::exception const& e) {
		std::cout
			<< "  testspr failed for some reason." << std::endl
			<< "  exception handled:" << std::endl
			<< "    type = " << testspr::typename_of(e) << std::endl
			<< "    what = " << e.what() << std::endl
			;
		return EXIT_FAILURE;
	} catch (...) {
		std::cout
			<< "  testspr failed for some reason." << std::endl
			<< "  exception handled:" << std::endl
			<< "    type = <unknown>" << std::endl
			;
		return EXIT_FAILURE;
	}
	std::cout << "  testspr succeeded." << std::endl;
}

#endif

#endif	// #ifndef TESTSPR_INCLUDE_MAIN_HPP
