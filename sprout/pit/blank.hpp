#ifndef SPROUT_PIT_BLANK_HPP
#define SPROUT_PIT_BLANK_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/array.hpp>
#include <sprout/pit/pit.hpp>

namespace sprout {
	//
	// blank
	//
	struct blank {};

	//
	// blank_pit
	//
	template<std::size_t N>
	inline SPROUT_CONSTEXPR sprout::pit<sprout::array<sprout::blank, N> >
	blank_pit() {
		return sprout::pit<sprout::array<sprout::blank, N> >();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_PIT_BLANK_HPP
