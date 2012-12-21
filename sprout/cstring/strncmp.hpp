#ifndef SPROUT_CSTRING_STRNCMP_HPP
#define SPROUT_CSTRING_STRNCMP_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/algorithm/tristate_lexicographical_compare.hpp>
#include <sprout/cstring/strlen.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// 7.21.4.4  strncmp ä÷êî
	inline SPROUT_CONSTEXPR int
	strncmp(char const* s1, char const* s2, std::size_t n) {
		return sprout::tristate_lexicographical_compare(
			sprout::as_iterator(s1), sprout::as_iterator(s1, sprout::strlen(s1, n)),
			sprout::as_iterator(s2), sprout::as_iterator(s2, sprout::strlen(s2, n))
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRNCMP_HPP
