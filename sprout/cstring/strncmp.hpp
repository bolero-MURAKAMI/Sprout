#ifndef SPROUT_CSTRING_STRNCMP_HPP
#define SPROUT_CSTRING_STRNCMP_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/type_traits/is_char_type.hpp>
#include <sprout/algorithm/tristate_lexicographical_compare.hpp>

namespace sprout {
	// 7.21.4.4  strncmp ä÷êî
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR int
	strncmp(char const* s1, char const* s2, std::size_t n) {
		return sprout::tristate_lexicographical_compare(
			sprout::as_iterator(s1), sprout::as_iterator(s1, n), '\0',
			sprout::as_iterator(s2), sprout::as_iterator(s2, n), '\0'
			);
	}

	template<typename Elem>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		sprout::is_char_type<Elem>::value,
		int
	>::type
	strncmp(Elem* s1, Elem* s2, std::size_t n) {
		typedef typename std::decay<Elem>::type type;
		return sprout::tristate_lexicographical_compare(
			sprout::as_iterator(s1), sprout::as_iterator(s1, n), type(),
			sprout::as_iterator(s2), sprout::as_iterator(s2, n), type()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRNCMP_HPP
