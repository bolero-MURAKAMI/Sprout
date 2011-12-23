#ifndef TESTSPR_PRINT_HPP
#define TESTSPR_PRINT_HPP

#include <algorithm>
#include <iterator>
#include <iostream>
#include <sprout/fixed_container.hpp>

namespace testspr {
	//
	// print
	//
	template<typename Iterator>
	void print(Iterator first, Iterator last) {
		std::for_each(first, last, [](typename std::iterator_traits<Iterator>::value_type const& e){ std::cout << e << ' '; });
		std::cout << std::endl;
	}
	template<typename Range>
	void print(Range const& range) {
		print(sprout::begin(range), sprout::end(range));
	}

	//
	// print_hl
	//
	void print_hl() {
		std::cout << "--------------------------------------------------------------------------------" << std::endl;
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_PRINT_HPP
