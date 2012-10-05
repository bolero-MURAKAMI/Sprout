#ifndef SPROUT_CSTDLIB_ATOF_HPP
#define SPROUT_CSTDLIB_ATOF_HPP

#include <sprout/config.hpp>
#include <sprout/cstdlib/str_to_float.hpp>

namespace sprout {
	//
	// atof
	//
	template<typename Char>
	inline SPROUT_CONSTEXPR double
	atof(Char const* str) {
		return sprout::str_to_float<double>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_ATOF_HPP
