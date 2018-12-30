/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <cstddef>
#include <type_traits>
#include <stdexcept>
#include <sprout/utility/any_convertible.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/array.hpp>
#include <sprout/string.hpp>
#include <sprout/random/default_random_engine.hpp>
#include <sprout/random/bernoulli_distribution.hpp>
#include <sprout/random/unique_seed.hpp>
#include <sprout/generator/functions.hpp>
#include <sprout/range/adaptor/reversed.hpp>
#include <sprout/algorithm/string/join.hpp>

static constexpr std::size_t default_limit = 96;

static constexpr std::size_t len = std::extent<std::remove_reference<decltype("キ・ヨ・シ！")>::type>::value - 1;
typedef sprout::string<len> string_type;

template<std::size_t N>
struct zundoko_result
	: public sprout::algorithm::results::join<sprout::array<string_type, N> >
{};
template<std::size_t N>
using zundoko_result_t = typename zundoko_result<N>::type;

inline constexpr string_type
zundoko(bool c) {
	return !c
		? sprout::to_string("ズン")
		: sprout::to_string("ドコ")
		;
}

template<
	std::size_t N, typename Rnd, typename... Args,
	typename sprout::enabler_if<!(sizeof...(Args) + 6 <= N)>::type = sprout::enabler
>
inline constexpr typename zundoko_result<N>::type
kiyoshi(Rnd const&, bool, bool, bool, bool, Args...) {
	return throw std::runtime_error("exceeded"), sprout::any_convertible();
}
template<
	std::size_t N, typename Rnd, typename... Args,
	typename sprout::enabler_if<(sizeof...(Args) + 6 <= N)>::type = sprout::enabler
>
inline constexpr typename zundoko_result<N>::type
kiyoshi(Rnd const& rnd, bool e0, bool e1, bool e2, bool e3, Args... args) {
	return !sprout::generated_value(rnd) || e0 || e1 || e2 || e3
		? kiyoshi<N>(sprout::next_generator(rnd)(), sprout::generated_value(rnd), e0, e1, e2, e3, args...)
		: sprout::algorithm::join(
			sprout::array<string_type, N>{{
				sprout::to_string("キ・ヨ・シ！"),
				zundoko(sprout::generated_value(rnd)),
				zundoko(e0), zundoko(e1), zundoko(e2), zundoko(e3),
				zundoko(args)...
				}}
				| sprout::adaptors::reversed
			)
		;
}
template<
	std::size_t N, typename Rnd, typename... Args,
	typename sprout::enabler_if<(sizeof...(Args) + 1 <= 4)>::type = sprout::enabler
>
inline constexpr typename zundoko_result<N>::type
kiyoshi(Rnd const& rnd, Args... args) {
	return kiyoshi<N>(sprout::next_generator(rnd)(), sprout::generated_value(rnd), args...);
}

template<
	std::size_t N = default_limit, typename URNG,
	typename sprout::enabler_if<!std::is_integral<URNG>::value>::type = sprout::enabler
>
inline constexpr typename zundoko_result<N>::type
zundoko_kiyoshi(URNG const& urng) {
	return kiyoshi<N>(sprout::bernoulli_distribution<>()(urng));
}
template<std::size_t N = default_limit>
inline constexpr typename zundoko_result<N>::type
zundoko_kiyoshi(std::size_t seed) {
	return zundoko_kiyoshi<N>(sprout::default_random_engine(seed));
}
template<std::size_t N = default_limit>
inline constexpr typename zundoko_result<N>::type
zundoko_kiyoshi() {
	return zundoko_kiyoshi<N>(SPROUT_UNIQUE_SEED);
}

#include <iostream>

int main() {
	constexpr auto result = zundoko_kiyoshi();
	std::cout << result;
}
