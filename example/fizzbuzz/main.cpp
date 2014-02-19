//
// Sprout C++ Library
//
// Copyright (c) 2012
// bolero-MURAKAMI : http://d.hatena.ne.jp/boleros/
// osyo-manga : http://d.hatena.ne.jp/osyo-manga/
// 
// Readme:
// https://github.com/bolero-MURAKAMI/Sprout/blob/master/README
//
// License:
// Boost Software License - Version 1.0
// <http://www.boost.org/LICENSE_1_0.txt>
//
#include <sprout/string.hpp>

struct fizzbuzz{
	typedef sprout::string<12> result_type;

	constexpr result_type
	operator()(int n) const {
		return n % 15 == 0 ? "FizzBuzz"
			 : n %  3 == 0 ? "Fizz"
			 : n %  5 == 0 ? "Buzz"
			 : sprout::to_string(n);
	}
};

//
// Test
//
static_assert(fizzbuzz()( 1) == "1",        "");
static_assert(fizzbuzz()( 2) == "2",        "");
static_assert(fizzbuzz()( 3) == "Fizz",     "");
static_assert(fizzbuzz()( 5) == "Buzz",     "");
static_assert(fizzbuzz()(15) == "FizzBuzz", "");



#include <sprout/array.hpp>
#include <sprout/algorithm/transform.hpp>
#include <sprout/numeric/iota.hpp>
#include <iostream>

int
main(){
	typedef fizzbuzz::result_type string;

	//
	// Sequence [1..15]
	//
	constexpr auto source = sprout::iota<sprout::array<int, 15> >(1);

	//
	// Transform to FizzBuzz
	//
	constexpr auto result = sprout::transform<sprout::array<string, 15> >(
		sprout::begin(source),
		sprout::end(source),
		fizzbuzz()
		);
	
	//
	// Check result
	//
	constexpr auto fizzbuzz_result = sprout::make_array<string>(
		"1", "2", "Fizz", "4", "Buzz",
		"Fizz", "7", "8", "Fizz", "Buzz",
		"11", "Fizz", "13", "14", "FizzBuzz"
		);
	// Equal result sequence
	static_assert(result == fizzbuzz_result, "");

	//
	// Output
	//
	for (auto&& str : result) {
		std::cout << str << ", ";
	}
	std::cout << std::endl;
}
