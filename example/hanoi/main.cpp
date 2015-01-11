/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/operation/push_back.hpp>
#include <sprout/operation/append_back.hpp>
#include <sprout/integer/static_pow.hpp>
#include <sprout/type_traits/enabler_if.hpp>

//
// hanoi
//
template<
	std::size_t N, typename Id,
	typename sprout::enabler_if<(N == 0)>::type = sprout::enabler
>
SPROUT_CONSTEXPR sprout::array<sprout::tuple<Id, Id, std::size_t>, 0>
hanoi(Id, Id, Id) {
	return sprout::array<sprout::tuple<Id, Id, std::size_t>, 0>{{}};
}
template<
	std::size_t N, typename Id,
	typename sprout::enabler_if<(N != 0)>::type = sprout::enabler
>
SPROUT_CONSTEXPR sprout::array<sprout::tuple<Id, Id, std::size_t>, sprout::static_pow2m1<std::size_t, N>::value>
hanoi(Id a, Id b, Id c) {
	typedef sprout::tuple<Id, Id, std::size_t> type;
	return sprout::append_back(
		sprout::push_back(hanoi<N - 1>(a, c, b), type(a, b, N)),
		hanoi<N - 1>(c, b, a)
		);
}

#include <iostream>

int main() {
	constexpr auto answer = hanoi<8>('a', 'b', 'c');
	for (auto const& e : answer) {
		std::cout << "disk " << sprout::get<2>(e) << ": " << sprout::get<0>(e) << " -> " << sprout::get<1>(e) << std::endl;
	}
}
