#ifndef SPROUT_STRING_COMPARISON_HPP
#define SPROUT_STRING_COMPARISON_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/string/string.hpp>

namespace sprout {
	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	inline SPROUT_CONSTEXPR bool operator==(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return lhs.compare(rhs) == 0;
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR bool operator==(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return lhs.compare(rhs) == 0;
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR bool operator==(T const* lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return 0 == rhs.compare(lhs);
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	inline SPROUT_CONSTEXPR bool operator!=(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR bool operator!=(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR bool operator!=(T const* lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	inline SPROUT_CONSTEXPR bool operator<(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return lhs.compare(rhs) < 0;
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR bool operator<(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return lhs.compare(rhs) < 0;
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR bool operator<(T const* lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return 0 < rhs.compare(lhs);
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	inline SPROUT_CONSTEXPR bool operator>(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR bool operator>(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR bool operator>(T const* lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	inline SPROUT_CONSTEXPR bool operator<=(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR bool operator<=(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR bool operator<=(T const* lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	inline SPROUT_CONSTEXPR bool operator>=(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR bool operator>=(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return !(lhs < rhs);
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR bool operator>=(T const* lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_COMPARISON_HPP
