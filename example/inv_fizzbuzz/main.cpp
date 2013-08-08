/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <sprout/array.hpp>
#include <sprout/string.hpp>
#include <sprout/utility.hpp>
#include <sprout/container.hpp>
#include <sprout/range.hpp>
#include <sprout/range/algorithm.hpp>
#include <sprout/range/adaptor.hpp>

static constexpr auto token_table = sprout::to_string_array<sprout::string<8> >(
	"Fizz", "Buzz", "Fizz", "Fizz", "Buzz", "Fizz", "FizzBuzz",
	"Fizz", "Buzz", "Fizz", "Fizz", "Buzz", "Fizz"
	);
static constexpr auto index_table = sprout::make_array<int>(
	3, 5, 6, 9, 10, 12, 15,
	18, 20, 21, 24, 25, 27
	);

template<typename ForwardRange, typename Difference>
constexpr sprout::pair<int, int>
inv_fizzbuzz_impl(ForwardRange const& rng, Difference found) {
	return found == sprout::size(token_table) ? sprout::pair<int, int>{0, 0}
		: sprout::pair<int, int>{
			index_table[found],
			sprout::size(rng) / 7 * 15 + index_table[found + sprout::size(rng) % 7 - 1]
			}
		;
}
template<typename ForwardRange>
constexpr sprout::pair<int, int>
inv_fizzbuzz(ForwardRange const& rng) {
	return sprout::size(rng) <= 7
		|| (sprout::size(sprout::range::find_end<sprout::range::return_found_end>(rng, rng | sprout::adaptors::taken(7))) == 7 + sprout::size(rng) % 7
			&& sprout::range::equal(
				rng | sprout::adaptors::taken(sprout::size(rng) % 7),
				rng | sprout::adaptors::dropped(sprout::size(rng) - sprout::size(rng) % 7)
				)
			)
		? inv_fizzbuzz_impl(
			rng,
			sprout::size(sprout::range::search<sprout::range::return_begin_found>(token_table, rng | sprout::adaptors::taken(7)))
			)
		: sprout::pair<int, int>{0, 0}
		;
}

#include <iostream>

template<typename ForwardRange, typename Pair>
void print(ForwardRange const& input, Pair const& answer) {
	std::cout << "input : ";
	for (auto const& e : input) {
		std::cout << e << ' ';
	}
	std::cout << std::endl;
	std::cout << "answer: (" << answer.first << ',' << answer.second << ')' << std::endl;
}

int main() {
	{
		constexpr auto input = sprout::to_string_array<sprout::string<8> >(
			"Fizz", "FizzBuzz", "Fizz", "Buzz"
			);
		constexpr auto answer = inv_fizzbuzz(input);

		static_assert(answer.first == 12 && answer.second == 20, "answer is (12,20)");
		print(input, answer);
	}
	{
		constexpr auto input = sprout::to_string_array<sprout::string<8> >(
			"FizzBuzz", "Fizz", "Buzz", "Fizz", "Fizz", "Buzz", "Fizz",
			"FizzBuzz", "Fizz", "Buzz", "Fizz", "Fizz", "Buzz", "Fizz",
			"FizzBuzz", "Fizz", "Buzz"
			);
		constexpr auto answer = inv_fizzbuzz(input);

		static_assert(answer.first == 15 && answer.second == 50, "answer is (15,50)");
		print(input, answer);
	}
	{
		constexpr auto input = sprout::to_string_array<sprout::string<8> >(
			"Fizz", "FizzBuzz", "Buzz"
			);
		constexpr auto answer = inv_fizzbuzz(input);

		static_assert(answer.first == 0 && answer.second == 0, "answer is (0,0)");
		print(input, answer);
	}
}
