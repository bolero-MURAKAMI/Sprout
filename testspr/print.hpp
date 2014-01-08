/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TESTSPR_PRINT_HPP
#define TESTSPR_PRINT_HPP

#include <algorithm>
#include <iterator>
#include <bitset>
#include <iostream>
#include <sprout/container.hpp>
#include <testspr/typeinfo.hpp>

namespace testspr {
	//
	// print
	//
	template<typename InputIterator>
	void print(InputIterator first, InputIterator last) {
		std::for_each(first, last, [](typename std::iterator_traits<InputIterator>::value_type const& e){ std::cout << e << ' '; });
		std::cout << std::endl;
	}
	template<typename InputRange>
	void print(InputRange const& range) {
		testspr::print(sprout::begin(range), sprout::end(range));
	}

	//
	// print_ln
	//
	void print_ln() {
		std::cout << std::endl;
	}
	template<typename T>
	void print_ln(T const& t) {
		std::cout << t << std::endl;
	}
	template<typename Head, typename... Tail>
	void print_ln(Head const& head, Tail const&... tail) {
		std::cout << head;
		testspr::print_ln(tail...);
	}

	//
	// print_bits
	//
	template<typename T>
	void print_bits(T const& t) {
		testspr::print_ln(std::bitset<sizeof(T) * 8>(t).template to_string<char>());
	}

	//
	// print_typename
	//
	template<typename T>
	void print_typename() {
		testspr::print_ln(testspr::typename_of<T>());
	}

	//
	// print_type
	//
	template<typename T>
	void print_type() {
		testspr::print_typename<testspr::id<T> >();
	}

	//
	// print_hl
	//
	void print_hl() {
		testspr::print_ln("--------------------------------------------------------------------------------");
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_PRINT_HPP
