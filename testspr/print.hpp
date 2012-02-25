#ifndef TESTSPR_PRINT_HPP
#define TESTSPR_PRINT_HPP

#include <algorithm>
#include <iterator>
#include <bitset>
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
		testspr::print(sprout::begin(range), sprout::end(range));
	}

	//
	// print_ln
	//
	template<typename T>
	static void print_ln(T const& t) {
		std::cout << t << std::endl;
	}

	//
	// print_bits
	//
	template<typename T>
	static void print_bits(T const& t) {
		testspr::print_ln(std::bitset<sizeof(T) * 8>(t).template to_string<char>());
	}

	//
	// print_hl
	//
	void print_hl() {
		testspr::print_ln("--------------------------------------------------------------------------------");
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_PRINT_HPP
